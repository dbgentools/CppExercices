#include "Exercice.hpp"
#include "Solution.hpp"
#include "TestUtils.hpp"

std::size_t operator"" _z(unsigned long long ii) { return static_cast<std::size_t>(ii); }

template<typename _Ty>concept a_vector = requires(_Ty t, typename _Ty::value_type v) {
  typename _Ty::value_type;
  { _Ty() };
  { _Ty(0_z) };
  { t.at(0_z) } -> std::same_as<const typename _Ty::value_type*>;
  { t.push_back(v) };
  { t.size() } -> std::same_as<std::size_t>;
  { t.clear() };
};

template<a_vector _VecTy>int test() {
  typename _VecTy::value_type v0{};
  _VecTy intvec{};
  TEST_EQ("Size check after init", intvec.size(), 0_z);
  intvec.push_back(v0);
  TEST_EQ("Size check after push", intvec.size(), 1_z);
  auto v0ptr = intvec.at(0);
  TEST_PTR("at pointer validity", v0ptr);
  TEST_EQ("at value correctness", *v0ptr, v0);
  const auto mt = random(16, 128);
  for(auto i = 0LL; i < mt; ++i)
    intvec.push_back(typename _VecTy::value_type{});
  TEST_EQ("Size check after x pushes", intvec.size(), mt + 1);
  intvec.clear();
  TEST_EQ("Size check after clear", intvec.size(), 0);
  intvec.push_back(v0);
  TEST_EQ("Size check after clear-push", intvec.size(), 1_z);
  return 0;
}

class TestElement {
  int specific = 0xdeadbeef;
public:
  TestElement() {}
  void set(int s) { specific = s; }
  bool operator==(const TestElement& r) { return specific == r.specific; };

  friend std::ostream& operator<< (std::ostream& stream, const TestElement& elem) {
    return stream << "TestElement{" << elem.specific << "}";
  }
};

int main(int, char**) {
  test<solution::SimpleVector<int>>();
  test<solution::SimpleVector<TestElement>>();

  test<excercice::SimpleVector<int>>();
  test<excercice::SimpleVector<TestElement>>();  

  std::cout << "All tests succeed...\n";
}