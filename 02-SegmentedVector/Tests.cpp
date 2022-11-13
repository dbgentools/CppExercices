#include "Exercice1.hpp"
#include "Exercice2.hpp"
#include "Solution.hpp"
#include "TestUtils.hpp"
#include <Windows.h>
#include <iostream>

std::size_t operator"" _z(unsigned long long ii) { return static_cast<std::size_t>(ii); }

template<typename _Base, std::integral _int>class IntProxy {
  _Base _base;
  _int data;
public:
  IntProxy() noexcept(noexcept(_Base{})) : IntProxy{ 0 } {}
  template<typename... _Ty>IntProxy(_int p, _Ty&&... args)
    : _base{ std::forward<_Ty>(args)... }, data{ p } {}

  constexpr operator _Base& () noexcept {
    return _base;
  }

  constexpr explicit operator _int() const noexcept {
    return data;
  }

  constexpr auto operator<=>(const IntProxy& p) const noexcept(noexcept(_Base::operator<=>)) {
    return data <=> p.data && _base <=> p._base;
  }
};

template<typename _Ty>concept req_ex1 = requires(_Ty t, typename _Ty::value_type v) {
  typename _Ty::value_type;
  { _Ty() };
  { t.at(0_z) } -> std::same_as<typename _Ty::value_type&>;
  { t.push_back(v) };
  { t.copy(&v,0_z) };
};

template<typename _Ty>concept req_ex2 = requires(_Ty t, typename _Ty::value_type v) {
  typename _Ty::value_type;
  requires req_ex1<_Ty>;
  { _Ty() };
  { t.reorganize(0_z,0_z) };
  { t.remove(0_z) };
  { t.is_lineary_full() } -> std::same_as<bool>;
};

static const char* ewhat;
static int _enum;

static constexpr auto tsize = 16ull * 16ull;
template<req_ex1 _Ex1>void _test1() {
  _enum = 1;
  using t1vt_t = IntProxy<typename _Ex1::value_type,decltype(0xbeef0007)>;
  t1vt_t vt[] = { {0xbeef0007}, { 0xbeef0008 }, { 0xbeef0009 } };
  _Ex1 intvec{};
  ewhat = "push_back";
  for (auto i{ 0ull }; i < tsize; ++i)
    intvec.push_back(vt[i % std::size(vt)]);
  ewhat = "at";
  for (auto i{ 0ull }; i < tsize; ++i)
    TEST_EQ("elem[i] pushed/looked correctly", intvec.at(i), vt[i % std::size(vt)]);
  typename _Ex1::value_type* tdest = new typename _Ex1::value_type[tsize];
  ewhat = "copy";
  intvec.copy(tdest, tsize);
  for (auto i{ 0ull }; i < tsize; ++i)
    TEST_EQ("elem[i] copied correctly", tdest[i], static_cast<typename _Ex1::value_type>(vt[i % std::size(vt)]));
}

void _sys_test_error() noexcept {
  TEST_NO_DIE(std::format("{} (e {}) throwed a system-level exception", ewhat, _enum));
}

void test(void(*fnc)()) {
  __try { fnc(); }
  __except (EXCEPTION_EXECUTE_HANDLER) {
      const volatile auto e = GetExceptionCode(); 
      _sys_test_error();
  }
}

class TestElement {
  int specific = 0xdeadbeef;
public:
  TestElement() {}
  void set(int s) { specific = s; }
  auto operator!=(const TestElement& r) const noexcept { return specific != r.specific; };

  friend std::ostream& operator<< (std::ostream& stream, const TestElement& elem) {
    return stream << "TestElement{" << elem.specific << "}";
  }
};

template<typename _Ex>void test1() {
  test(_test1<_Ex>);
}

int main(int, char**) {
  test1<solution::SegmentedVector<int>>();
  test1<solution::SegmentedVector<TestElement>>();

  //test1<exercice1::SegmentedVector<int>>();
  //test1<exercice1::SegmentedVector<TestElement>>();

  /*std::cout << "Test excercice 1 succeed...\n";

  test2<solution::SegmentedVector<int>>();
  test2<solution::SegmentedVector<TestElement>>();

  test2<exercice1::SegmentedVector<int>>();
  test2<exercice1::SegmentedVector<TestElement>>();*/
  std::cout << "All tests succeed...\n";
}