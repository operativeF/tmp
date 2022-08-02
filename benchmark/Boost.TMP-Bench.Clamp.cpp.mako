import Boost.TMP;

using namespace boost::tmp;
<%
iters = range(iterations)
%>
% for i in iters:
using size_bench_${i} = call_<size_<>, int_<1>, int_<2>, char_<'c'>>;
size_bench_${i} foo_${i}{};
% endfor

int main() {}
