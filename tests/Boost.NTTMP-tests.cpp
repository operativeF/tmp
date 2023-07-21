
namespace is_v_tests {

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueIsFive;

using is_v_test_1 = ValueIsFive<call_v_<is_v_<5>, 5>>;

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueCharCIsInt99;

using is_v_test_2 = ValueCharCIsInt99<call_v_<is_v_<99>, 'c'>>;

} // namespace is_v_tests

namespace is_not_v_tests {

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueIsNotFive;

using is_not_v_test_1 = ValueIsNotFive<call_v_<is_not_v_<5>, 2>>;

} // namespace is_v_tests

namespace not_v_tests {

template<typename T> requires(std::same_as<T, list_v_<true>>)
struct ValueIsNotTrue;

using not_v_test_1 = ValueIsNotTrue<call_v_<not_v_<>, false>>;

} // namespace not_v_tests
