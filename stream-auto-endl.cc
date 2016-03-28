#include <iostream>

// Here we define our application severity levels.
enum severityLevel {
   TRACE,
   DEBUG,
   INFO,
   WARNING,
   ERROR,
   FATAL
};

severityLevel g_log_level = TRACE;

// The formatting logic for the severity level
template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<< (std::basic_ostream<CharT, TraitsT>& strm, severityLevel lvl)
{
   switch (lvl) {
   case TRACE:
      strm << "TRACE"; break;
   case DEBUG:
      strm << "DEBUG"; break;
   case INFO:
      strm << "INFO"; break;
   case WARNING:
      strm << "WARNING"; break;
   case ERROR:
      strm << "ERROR"; break;
   case FATAL:
      strm << "FATAL"; break;
   default:
      strm << static_cast<int>(lvl); break;
   }
   return strm;
}

class logger {
public:
  logger(severityLevel l, std::ostream& s)
    : level(l), stream(s)
  {
    (*this) << level << ": ";
  }

  ~logger()
  {
    (*this) << std::endl;
  }

private:

  template <class T>
  friend const logger& operator<<(const logger&, const T&);

  friend const logger& operator<<(const logger& l, std::ostream& (*manip)(std::ostream&));

  severityLevel level;
  std::ostream& stream;

};

template <class T>
const logger& operator<<(const logger& l, const T& value)
{
  if (l.level >= g_log_level)
    l.stream << value;
  return l;
}

const logger& operator<<(const logger& l, std::ostream& (*manip)(std::ostream&))
{
  manip(l.stream);
  return l;
}

int main(int argc, char *argv[])
{
  logger(TRACE, std::cout) << "foo" << std::endl << "bar" << 42;
  return 0;
}
