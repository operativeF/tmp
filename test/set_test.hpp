#include <boost/tmp/sequence/push_front.hpp>
#include <boost/tmp/sequence/set.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace set_test {
	using namespace boost::tmp;
	using test = call_<make_unique, int_<1>, int_<2>, int_<1>, int_<2>>;
	int run() {
        return 0;
	}
} // namespace set_test