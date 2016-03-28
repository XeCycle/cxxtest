#include <cstdint>
#include <iostream>
#include <vector>
#include <functional>
#include <iterator>

#include <bs3/pbs.hh>

#include <daq-raw-reader.hh>

#define LAZY true

namespace dr = daq_raw;
namespace pu = pbs::utils;

using pu::optional;
using pu::nullopt;

template <class Iterable>
struct print_iterable_t {
  const Iterable& values;
};

using std::begin;

template <class Iterable>
auto operator<<(std::ostream& out, const print_iterable_t<Iterable>& wrapper)
  -> decltype(out << *begin(wrapper.values))
{
  out << '[';

  auto first = begin(wrapper.values);
  auto last = end(wrapper.values);
  if (first != last) {
    out << *first;
    for (++first; first!=last; ++first)
      out << ',' << *first;
  }

  return out << ']';
}

template <class Iterable>
print_iterable_t<Iterable>
print_iterable(const Iterable& values)
{
  return { values };
}

struct SamplePoint {
  int32_t time;
  uint16_t value;

  bool operator==(const SamplePoint& other) const
  {
    return time == other.time && value == other.value;
  }
};

std::ostream& operator<<(std::ostream& out, const SamplePoint& pt)
{
  return out << '[' << pt.time << ',' << pt.value << ']';
  // char x = pt.time & pt.value;
  // return out << x;
}

using std::begin;

template <class OuterIterator>
struct flattening_iterator {

  typedef OuterIterator outer_iterator;
  typedef typename std::decay<decltype(begin(std::declval<typename std::iterator_traits<outer_iterator>::value_type&>()))>::type inner_iterator;

  typedef typename std::iterator_traits<inner_iterator>::value_type value_type;
  typedef typename std::iterator_traits<inner_iterator>::reference reference;
  typedef typename std::iterator_traits<inner_iterator>::pointer pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

private:

  outer_iterator outer, outer_end;
  optional<std::pair<inner_iterator, inner_iterator> > current;

  void skip_to_valid()
  {
    while (outer != outer_end) {
      if (!current)
        current = std::make_pair(begin(*outer), end(*outer));
      if (current->first != current->second)
        return;
      else
        current = nullopt, ++outer;
    }
  }

public:

  flattening_iterator(const outer_iterator& _outer, const outer_iterator& _outer_end)
    : outer(_outer), outer_end(_outer_end)
  {
    skip_to_valid();
  }

  reference operator*() const
  {
    return *current->first;
  }

  pointer operator->() const
  {
    return &(*(*this));
  }

  flattening_iterator& operator++()
  {
    ++current->first;
    skip_to_valid();
    return *this;
  }

  flattening_iterator operator++(int)
  {
    auto copy = *this;
    ++*this;
    return copy;
  }

  bool operator==(const flattening_iterator& other) const
  {
    return outer==other.outer && outer_end==other.outer_end && current==other.current;
  }

  bool operator!=(const flattening_iterator& other) const
  {
    return !((*this) == other);
  }

};

using std::begin;
using std::end;

template <class Iterable>
pbs::utils::range<flattening_iterator<decltype(begin(std::declval<Iterable&>()))> >
flatten(Iterable&& r)
{
  return { {begin(r), end(r)}, {end(r), end(r)} };
}

using pbs::utils::map;
using pbs::utils::map_indexed;

template <class Function, class Iterable>
auto flat_map(Function f, Iterable&& r)
  -> decltype(flatten(map(f, r)))
{
  return flatten(map(f, r));
}

struct expander {
  int32_t time;
  SamplePoint operator()(uint16_t value, int32_t index) const
  {
    return { time+index, value };
  }
};

auto expand_segment(const pbt::RawPmtSegment& seg)
  -> decltype(map_indexed(std::declval<expander>(), seg.adcValue))
{
  return map_indexed(expander { seg.startTime }, seg.adcValue);
}

#if LAZY

auto expand_waveform(const std::vector<pbt::RawPmtSegment>& wf)
  -> decltype(flat_map(expand_segment, wf))
{
  return flat_map(expand_segment, wf);
}

#else

// [Segment] -> [Point]
std::vector<SamplePoint>
expand_waveform(const std::vector<pbt::RawPmtSegment>& wf)
{
  std::vector<SamplePoint> output;

  auto total = pu::reduce(
    std::plus<size_t>(),
    pu::map([](const pbt::RawPmtSegment& seg) { return seg.adcValue.size(); }, wf));
  output.reserve(total);

  for (auto& seg : wf) {
    auto time = seg.startTime;
    for (auto& sample : seg.adcValue)
      output.push_back({ time++, sample });
  }

  return output;
}

#endif

// (Size, [Point]) -> [Point]
// return at most count*2 points
//
// Break up `in` into `count` windows, and each window is reduced to a min
// and max, if both are present, retaining original time position.  If min
// and max are the same then the window becomes a single point; empty
// window becomes nothing.
//
// `in` must be ascending ordered by time.

#if true

template <class Finder, class Iterator>
struct window_iterator {

  typedef std::forward_iterator_tag iterator_category;
  typedef pbs::utils::range<Iterator> value_type;
  typedef value_type reference;
  typedef std::unique_ptr<value_type> pointer;
  typedef std::ptrdiff_t difference_type;

private:
  Finder _finder;
  Iterator _first;
  const Iterator _end;
  Iterator _last;

public:

  window_iterator(Finder finder, Iterator begin, Iterator end)
    : _finder(finder), _first(begin), _end(end), _last(_finder(_first, _end))
  {}

  reference operator*() const
  {
    return { _first, _last };
  }

  window_iterator& operator++()
  {
    _first = _last;
    _last = _finder(_first, _end);
    return *this;
  }

  bool operator==(const window_iterator& other) const
  {
    return _first==other._first && _end==other._end
      // these two are unlikely to be false, if above are true
      && _last==other._last;
  }

  bool operator!=(const window_iterator& other) const
  {
    return !((*this)==other);
  }

};

template <class Function, class Iterator>
pbs::utils::range<window_iterator<typename std::decay<Function>::type,
                      typename std::decay<Iterator>::type> >
window_by(Function&& f, Iterator&& first, typename std::enable_if<true, Iterator>::type&& last)
{
  return { {f, first, last}, {f, last, last} };
}

template <class Function, class Range>
auto window_by(Function&& f, Range&& r)
  -> decltype(window_by(std::forward<Function>(f), begin(r), end(r)))
{
  return window_by(std::forward<Function>(f), begin(r), end(r));
}

struct window_end_finder {
  size_t count;
  int32_t end_time;
  size_t i_window;
  template <class Iterator>
  Iterator operator()(Iterator first, Iterator last)
  {
    int32_t high = end_time * (i_window+1) / count;
    ++i_window;
    return std::find_if(
      first, last,
      [=](const SamplePoint& p) { return p.time >= high; });
  }
};

struct reduce_window {
  template <class Range>
  std::vector<SamplePoint> operator()(Range&& window) const
  {
    if (begin(window) == end(window))
      return {};
    auto min=*begin(window), max=*begin(window);
    for (const auto& point : window) {
      if (point.value < min.value) min = point;
      if (point.value > max.value) max = point;
    }
    if (min.time == max.time)
      return { min };
    else if (min.time < max.time)
      return { min, max };
    else // max.time < min.time
      return { max, min };
  }
};

auto down_sample(size_t count, const std::vector<pbt::RawPmtSegment>& input)
  -> decltype(flat_map(
                reduce_window(),
                window_by(
                  std::declval<window_end_finder>(),
                  expand_waveform(input))))
{
  auto in = expand_waveform(input);
  int32_t end_time = 1+ input.back().startTime + input.back().adcValue.size();

  return flat_map(
    reduce_window(),
    window_by(
      window_end_finder{count, end_time, 0},
      in));
}

#else

std::vector<SamplePoint>
down_sample(size_t count, const std::vector<pbt::RawPmtSegment>& input)
{
  std::vector<SamplePoint> out;
  out.reserve(2*count);

  auto write = [&](const SamplePoint& p) { out.push_back(p); };

  int32_t end_time = 1+ input.back().startTime + input.back().adcValue.size();
  auto in = expand_waveform(input);

  {
    auto window_begin = in.begin();
    for (size_t i_window=0; i_window<count; ++i_window) {
      // auto low = end_time * i_window / count;
      int32_t high = end_time * (i_window+1) / count;
      const auto window_end = std::find_if(
        window_begin, in.end(),
        [=](const SamplePoint& p) { return p.time >= high; });

      if (window_begin == window_end)
        continue;
      else {
        auto min=*window_begin, max=*window_begin;
        for (const auto& point : pu::make_range(++window_begin, window_end)) {
          if (point.value < min.value) min = point;
          if (point.value > max.value) max = point;
        }
        if (min.time == max.time)
          write(min);
        else if (min.time < max.time)
          write(min), write(max);
        else // max.time < min.time
          write(max), write(min);
      }

      window_begin = window_end;
    }
  }

  return out;
}

#endif

template <class Iterable>
char silly_checksum(const Iterable&& i)
{
  char x=0;
  for (auto first=begin(i); first!=end(i); ++first)
    x |= reinterpret_cast<const char&>(*&*first);
  return x;
}

int main()
{

  using std::cout;

  for (const auto& event : dr::read_file(std::cin)) {
    cout << "{\"run\":" << event.runNumber
         << ",\"event\":" << event.eventNumber
         << ",\"waveforms\":{";
    bool first = true;
    for (auto& wfpair : event.rawWaveforms) {
      if (first)
        first = false;
      else
        cout << ',';
      cout << '"' << wfpair.first << "\":"
           << print_iterable(down_sample(500, wfpair.second));
    }
    cout << "}}\n";
  }

  return 0;
}
