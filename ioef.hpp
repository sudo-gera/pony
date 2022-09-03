



template<typename T>
auto check_4(const T&q){
    auto[q1,q2,q3,q4]=q;
}

template<typename T1,typename T2>
auto for_each_field(const T1&q,const T2&f)->decltype(check_4(q)){
    auto[q1,q2,q3,q4]=q;
    f(q1,q2,q3,q4);
}

template<typename T>
auto check_5(const T&q){
    auto[q1,q2,q3,q4,q5]=q;
}

template<typename T1,typename T2>
auto for_each_field(const T1&q,const T2&f)->decltype(check_5(q)){
    auto[q1,q2,q3,q4,q5]=q;
    f(q1,q2,q3,q4,q5);
}