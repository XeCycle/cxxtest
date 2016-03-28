
#if __cplusplus >= 201103L

#include <shared_ptr>
using std::shared_ptr;

#else

#include <tr1/shared_ptr>
using std::tr1::shared_ptr;

#endif

class TRestEventProcessComposed : public TRestEventProcess {

  typedef shared_ptr<TRestEventProcessComposed> process_ptr;

  process_ptr left, right;

public:

  TRestEventProcessComposed(process_ptr l, process_ptr r)
    : left(l), right(r)
  {}

  void InitProcess()
  {
    l->InitProcess();
    r->InitProcess();
  }

  TRestEvent* ProcessEvent(TRestEvent* evInput)
  {
    return r->ProcessEvent(l->ProcessEvent(evInput));
  }

  void EndProcess()
  {
    l->EndProcess();
    r->EndProcess();
  }

  void BeginOfEventProcess()
  {
    l->BeginOfEventProcess();
    r->BeginOfEventProcess();
  }

  void EndOfEventProcess()
  {
    l->EndOfEventProcess();
    r->EndOfEventProcess();
  }

  TString GetProcessName()
  {
    TString name;
    name += l->GetProcessName();
    name += " then ";
    name += r->GetProcessName();
    return name;
  }

};

class TRestEventProcessComposedInParallel : public TRestEventProcess {

  typedef shared_ptr<TRestEventProcessComposed> process_ptr;

#ifndef __CINT__
  process_ptr left, right;
#endif

public:

  TRestEventProcessComposed(process_ptr l, process_ptr r)
    : left(l), right(r)
  {}

  void InitProcess()
  {
    l->InitProcess();
    r->InitProcess();
  }

  TRestEvent* ProcessEvent(TRestEvent* evInput)
  {
    l->ProcessEvent(evInput);
    r->ProcessEvent(evInput);
  }

  void EndProcess()
  {
    l->EndProcess();
    r->EndProcess();
  }

  void BeginOfEventProcess()
  {
    l->BeginOfEventProcess();
    r->BeginOfEventProcess();
  }

  void EndOfEventProcess()
  {
    l->EndOfEventProcess();
    r->EndOfEventProcess();
  }

  TString GetProcessName()
  {
    TString name;
    name += l->GetProcessName();
    name += " then ";
    name += r->GetProcessName();
    return name;
  }

};

class TRestEventProcessComposedInParallel : public TRestEventProcess {

  typedef shared_ptr<TRestEventProcessComposed> process_ptr;

#ifndef __CINT__
  process_ptr left, right;
#endif

public:

  TRestEventProcessComposed(process_ptr l, process_ptr r)
    : left(l), right(r)
  {}

  void InitProcess()
  {
    l->InitProcess();
    r->InitProcess();
  }

  TRestEvent* ProcessEvent(TRestEvent* evInput)
  {
    l->ProcessEvent(evInput);
    r->ProcessEvent(evInput);
  }

  void EndProcess()
  {
    l->EndProcess();
    r->EndProcess();
  }

  void BeginOfEventProcess()
  {
    l->BeginOfEventProcess();
    r->BeginOfEventProcess();
  }

  void EndOfEventProcess()
  {
    l->EndOfEventProcess();
    r->EndOfEventProcess();
  }

  TString GetProcessName()
  {
    TString name;
    name += l->GetProcessName();
    name += " then ";
    name += r->GetProcessName();
    return name;
  }

};
