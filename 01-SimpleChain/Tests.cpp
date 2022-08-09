#include "Exercice.hpp"
#include "Solution.hpp"
#include "TestUtils.hpp"

std::size_t operator"" _z(unsigned long long ii) { return static_cast<std::size_t>(ii); }

template<typename _Ty>concept a_chain = requires(_Ty t, typename _Ty::value_type v) {
  typename _Ty::value_type;
  { _Ty() };
  { t.at(0_z) } -> std::same_as<typename _Ty::value_type*>;
  { t.first() } -> std::same_as<typename _Ty::value_type*>;
  { t.last() } -> std::same_as<typename _Ty::value_type*>;
  { t.push_back(&v) } -> std::same_as<std::size_t>;
  { t.size() } -> std::same_as<std::size_t>;
  { t.clear() };
  { t.remove(0_z) };
};

template<a_chain _ChainTy>int test() {
  typename _ChainTy::value_type v0{}, v1{}, v2{};
  _ChainTy intvec{};
  TEST_EQ("Size check after init", intvec.size(), 0_z);
  intvec.push_back(&v0);
  TEST_EQ("Size check after push", intvec.size(), 1_z);
  auto v0ptr = intvec.at(0);
  TEST_PTR("at pointer validity", v0ptr);
  TEST_EQ("at value correctness", v0ptr, &v0);
  TEST_PTR("safe at check", !intvec.at(15));
  const auto mt = random(16, 128);
  typename _ChainTy::value_type* vals = new typename _ChainTy::value_type[mt];
  for (auto i = 0LL; i < mt; ++i)
    TEST_EQ("push_back return value", intvec.push_back(&vals[i]), i+1);
  TEST_EQ("Size check after x pushes", intvec.size(), mt + 1);
  for (auto i = 0LL; i < mt; ++i)
    TEST_EQ("at correcness for x pushes", intvec.at(i+1), &vals[i]);
  intvec.clear();
  TEST_EQ("Size check after clear", intvec.size(), 0);
  intvec.push_back(&v0);
  TEST_EQ("Size check after clear-push", intvec.size(), 1_z);
  intvec.push_back(&v0);
  intvec.push_back(&v1);
  intvec.push_back(&v2);
  intvec.remove(0); // Remove first
  TEST_EQ("Size check after remove", intvec.size(), 3_z);
  TEST_EQ("at 0 value correctness after remove f", intvec.at(0), &v0);
  TEST_EQ("at 1 value correctness after remove f", intvec.at(1), &v1);
  TEST_EQ("at 2 value correctness after remove f", intvec.at(2), &v2);
  intvec.remove(1); // Remove standard
  TEST_EQ("at 0 value correctness after remove s", intvec.at(0), &v0);
  TEST_EQ("at 2 value correctness after remove s", intvec.at(1), &v2);
  intvec.remove(1); // Remove last
  TEST_EQ("at 0 value correctness after remove l", intvec.at(0), &v0);
  intvec.remove(0); // Remove only
  TEST_EQ("Size check after remove all", intvec.size(), 0_z);
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
  test<solution::SimpleChain<int>>();
  test<solution::SimpleChain<TestElement>>();

  test<exercice::SimpleChain<int>>();
  test<exercice::SimpleChain<TestElement>>();

  std::cout << "All tests succeed...\n";
}