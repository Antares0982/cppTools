#pragma once

#include <utility>

/// @brief A virtual private method caller.
///  To use this on a method `f` in object `a` of class `A`,
///  declare a new class as
///  `class B : public A, public TVirtualPrivateCaller<B>`
///  and override the desired method `f` in `B` with public keyword.
///  Then use
///  `B::Call(&B::f, a, args...)` to call the private method.
template <typename TThisType>
class TVirtualPrivateCaller
{
public:
    template <typename TMethodAddress, typename TSuperClass, typename... TArgs>
    static auto Call(TMethodAddress MethodAddr, TSuperClass &ToCallInstance, TArgs &&...Args)
    {
        return (static_cast<TThisType &>(ToCallInstance).*MethodAddr)(std::forward<TArgs>(Args)...);
    }

    template <typename TMethodAddress, typename TSuperClass, typename... TArgs>
    static auto Call(TMethodAddress MethodAddr, const TSuperClass &ToCallInstance, TArgs &&...Args)
    {
        return (static_cast<const TThisType &>(ToCallInstance).*MethodAddr)(std::forward<TArgs>(Args)...);
    }
};

/// @brief A non-virtual (virtual methods can also be applied) private method caller.
///  To use this on a method `f` of class `A`, declare a struct `Tag` as
///  `struct Tag{ using Type = RTType(A::*)(ArgsType...); };`
///  and explicitly instantiate `CallTNonVirtualPrivateSetter` as
///  `template class CallTNonVirtualPrivateSetter<Tag, &A::f>;`
///  Then use
///  `TNonVirtualPrivateCaller<Af>::Call(object_may_be_const, args...)`
///  to call the private method.
/// @see https://stackoverflow.com/questions/6873138/calling-private-method-in-c
template <typename Tag>
struct TNonVirtualPrivateCaller
{
    /* export it ... */
    typedef typename Tag::Type Type;
    static Type MethodPtr;
    template <typename Kls, typename... TArgs>
    static auto Call(Kls &Ptr, TArgs &&...Args)
    {
        return (Ptr.*MethodPtr)(std::forward<TArgs>(Args)...);
    }
};

template <typename Tag>
typename TNonVirtualPrivateCaller<Tag>::Type TNonVirtualPrivateCaller<Tag>::MethodPtr;

template <typename Tag, typename Tag::Type InPtr>
class CallTNonVirtualPrivateSetter : TNonVirtualPrivateCaller<Tag>
{
    /* fill it ... */
    struct FSetter
    {
        FSetter() { TNonVirtualPrivateCaller<Tag>::MethodPtr = InPtr; }
    };
    static FSetter FillerObj;
};

template <typename Tag, typename Tag::Type InPtr>
typename CallTNonVirtualPrivateSetter<Tag, InPtr>::FSetter CallTNonVirtualPrivateSetter<Tag, InPtr>::FillerObj;
