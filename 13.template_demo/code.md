```cpp
template <typename T>
struct HasValue {
  template <typename U>
  static std::true_type test(decltype(&U::value));

  template <typename U>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
typename std::enable_if<HasValue<T>::value>::type
printValue(T arg) {
  std::cout << "Value: " << arg.value << std::endl;
}

struct MyStruct {
  int value = 42;
};

struct MyOtherStruct {
  float otherValue = 3.14f;
  int value = 43;
};

int main() {
  MyStruct s;
  MyOtherStruct os;

  printValue(s); // 输出：Value: 42

  // 下面这行代码会在编译时出现错误，因为MyOtherStruct类型不满足HasValue的限定条件
  printValue(os);
}
```
