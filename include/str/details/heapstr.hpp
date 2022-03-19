// template <typename Char, typename CharTraits, typename Allocator>
// class basic_str<Char, CharTraits, Allocator>::iterator
// {
//     using this_t = str_iterator<Str>;
//     using source_t = basic_str<Char, CharTraits, Allocator>;

// public:
//     using iterator_category = random_access_iterator_tag;
//     using value_type = typename source_t::value_type;
//     using difference_type = typename source_t::difference_type;
//     using pointer = typename source_t::pointer;
//     using reference = typename source_t::reference;

//     STR_CONSTEXPR_20 iterator() STR_NOEXCEPT : ptr_{nullptr} {}
//     STR_CONSTEXPR_20 iterator(pointer ptr) STR_NOEXCEPT : ptr_(ptr) {}
//     STR_CONSTEXPR_20 ~iterator() STR_NOEXCEPT = default;

//     STR_NODISCARD STR_CONSTEXPR_20 reference operator*() const STR_NOEXCEPT
//     {
//         return *ptr_;
//     }

//     STR_NODISCARD STR_CONSTEXPR_20 pointer operator->() const STR_NOEXCEPT
//     {
//         return pointer_traits<pointer>::pointer_to(**this);
//     }

//     STR_CONSTEXPR_20 this_t &operator++() STR_NOEXCEPT
//     {
//         ++ptr_;
//         return *this;
//     }

//     STR_CONSTEXPR_20 this_t operator++(int) STR_NOEXCEPT
//     {
//         this_t tmp = *this;
//         ++*this;
//         return tmp;
//     }

//     STR_CONSTEXPR_20 this_t &operator--() STR_NOEXCEPT
//     {
//         --ptr_;
//         return *this;
//     }

//     STR_CONSTEXPR_20 this_t operator--(int) STR_NOEXCEPT
//     {
//         this_t tmp = *this;
//         --*this;
//         return tmp;
//     }

//     STR_CONSTEXPR_20 void _Verify_offset(const difference_type _Off) const STR_NOEXCEPT
//     {
// #if _ITERATOR_DEBUG_LEVEL >= 1
//         if (_Off == 0)
//         {
//             return;
//         }

//         _STL_ASSERT(ptr_, "cannot seek value-initialized string iterator");
//         const auto _Mycont = static_cast<const Str *>(this->_Getcont());
//         _STL_ASSERT(_Mycont, "cannot seek string iterator because the iterator was"
//                              " invalidated (e.g. reallocation occurred, or the string was destroyed)");
//         const auto _Contptr = _Mycont->_Myptr();
//         const auto _Rawptr = _Unfancy(ptr_);

//         if (_Off < 0)
//         {
//             _STL_VERIFY(_Contptr - _Rawptr <= _Off, "cannot seek string iterator before begin");
//         }

//         if (_Off > 0)
//         {
//             using _Size_type = typename Str::size_type;
//             const auto _Left = _Mycont->_Mysize - static_cast<_Size_type>(_Rawptr - _Contptr);
//             _STL_VERIFY(static_cast<_Size_type>(_Off) <= _Left, "cannot seek string iterator after end");
//         }
// #else  // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
//         (void)_Off;
// #endif // _ITERATOR_DEBUG_LEVEL >= 1
//     }

//     STR_CONSTEXPR_20 this_t &operator+=(const difference_type _Off) STR_NOEXCEPT
//     {
// #if _ITERATOR_DEBUG_LEVEL >= 1
//         _Verify_offset(_Off);
// #endif // _ITERATOR_DEBUG_LEVEL >= 1
//         ptr_ += _Off;
//         return *this;
//     }

//     STR_NODISCARD STR_CONSTEXPR_20 this_t operator+(const difference_type _Off) const STR_NOEXCEPT
//     {
//         this_t _Tmp = *this;
//         _Tmp += _Off;
//         return _Tmp;
//     }

//     STR_CONSTEXPR_20 this_t &operator-=(const difference_type _Off) STR_NOEXCEPT
//     {
//         return *this += -_Off;
//     }

//     STR_NODISCARD STR_CONSTEXPR_20 this_t operator-(const difference_type _Off) const STR_NOEXCEPT
//     {
//         this_t _Tmp = *this;
//         _Tmp -= _Off;
//         return _Tmp;
//     }

//     STR_NODISCARD STR_CONSTEXPR_20 difference_type operator-(const this_t &_Right) const STR_NOEXCEPT
//     {
//         _Compat(_Right);
//         return ptr_ - _Right.ptr_;
//     }

//     STR_NODISCARD STR_CONSTEXPR_20 reference operator[](const difference_type _Off) const STR_NOEXCEPT
//     {
//         return *(*this + _Off);
//     }

//     STR_NODISCARD STR_CONSTEXPR_20 bool operator==(const this_t &_Right) const STR_NOEXCEPT
//     {
//         _Compat(_Right);
//         return ptr_ == _Right.ptr_;
//     }

// #if _HAS_CXX20
//     STR_NODISCARD STR_CONSTEXPR strong_ordering operator<=>(const this_t &_Right) const STR_NOEXCEPT
//     {
//         _Compat(_Right);
//         return _Unfancy(ptr_) <=> _Unfancy(_Right.ptr_);
//     }
// #else
//     STR_NODISCARD bool operator!=(const this_t &_Right) const STR_NOEXCEPT
//     {
//         return !(*this == _Right);
//     }

//     STR_NODISCARD bool operator<(const this_t &_Right) const STR_NOEXCEPT
//     {
//         _Compat(_Right);
//         return ptr_ < _Right.ptr_;
//     }

//     STR_NODISCARD bool operator>(const this_t &_Right) const STR_NOEXCEPT
//     {
//         return _Right < *this;
//     }

//     STR_NODISCARD bool operator<=(const this_t &_Right) const STR_NOEXCEPT
//     {
//         return !(_Right < *this);
//     }

//     STR_NODISCARD bool operator>=(const this_t &_Right) const STR_NOEXCEPT
//     {
//         return !(*this < _Right);
//     }
// #endif // !_HAS_CXX20

//     STR_CONSTEXPR_20 void _Compat(const this_t &_Right) const STR_NOEXCEPT
//     {
//         // test for compatible iterator pair
// #if _ITERATOR_DEBUG_LEVEL >= 1
//         _STL_VERIFY(this->_Getcont() == _Right._Getcont(), "string iterators incompatible (e.g."
//                                                            " point to different string instances)");
// #else  // ^^^ _ITERATOR_DEBUG_LEVEL >= 1 ^^^ // vvv _ITERATOR_DEBUG_LEVEL == 0 vvv
//         (void)_Right;
// #endif // _ITERATOR_DEBUG_LEVEL
//     }

// #if _ITERATOR_DEBUG_LEVEL >= 1
//     friend STR_CONSTEXPR_20 void _Verify_range(
//         const this_t &_First, const this_t &_Last) STR_NOEXCEPT
//     {
//         _STL_VERIFY(_First._Getcont() == _Last._Getcont(), "string iterators in range are from different containers");
//         _STL_VERIFY(_First.ptr_ <= _Last.ptr_, "string iterator range transposed");
//     }
// #endif // _ITERATOR_DEBUG_LEVEL >= 1

//     using _Prevent_inheriting_unwrap = this_t;

//     STR_NODISCARD STR_CONSTEXPR_20 const value_type *_Unwrapped() const STR_NOEXCEPT
//     {
//         return _Unfancy(ptr_);
//     }

//     STR_CONSTEXPR_20 void _Seek_to(const value_type *_It) STR_NOEXCEPT
//     {
//         ptr_ = _Refancy<pointer>(const_cast<value_type *>(_It));
//     }

//     pointer ptr_;
// };







// template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
// class basic_string { // null-terminated transparent array of elements
// private:
//     friend _Tidy_deallocate_guard<basic_string>;
//     friend basic_stringbuf<_Elem, _Traits, _Alloc>;

//     using _Alty        = _Rebind_alloc_t<_Alloc, _Elem>;
//     using _Alty_traits = allocator_traits<_Alty>;

//     using _Scary_val = _String_val<conditional_t<_Is_simple_alloc_v<_Alty>, _Simple_types<_Elem>,
//         _String_iter_types<_Elem, typename _Alty_traits::size_type, typename _Alty_traits::difference_type,
//             typename _Alty_traits::pointer, typename _Alty_traits::const_pointer, _Elem&, const _Elem&>>>;

//     static_assert(!_ENFORCE_MATCHING_ALLOCATORS || is_same_v<_Elem, typename _Alloc::value_type>,
//         _MISMATCHED_ALLOCATOR_MESSAGE("basic_string<T, Traits, Allocator>", "T"));

//     static_assert(is_same_v<_Elem, typename _Traits::char_type>,
//         "N4659 24.3.2.1 [string.require]/3 requires that the supplied "
//         "char_traits character type match the string's character type.");

//     static_assert(!is_array_v<_Elem> && is_trivial_v<_Elem> && is_standard_layout_v<_Elem>,
//         "The character type of basic_string must be a non-array trivial standard-layout type. See N4861 "
//         "[strings.general]/1.");

// public:
//     using traits_type    = _Traits;
//     using allocator_type = _Alloc;

//     using value_type      = _Elem;
//     using size_type       = typename _Alty_traits::size_type;
//     using difference_type = typename _Alty_traits::difference_type;
//     using pointer         = typename _Alty_traits::pointer;
//     using const_pointer   = typename _Alty_traits::const_pointer;
//     using reference       = value_type&;
//     using const_reference = const value_type&;

//     using iterator       = _String_iterator<_Scary_val>;
//     using const_iterator = _String_const_iterator<_Scary_val>;

//     using reverse_iterator       = _STD reverse_iterator<iterator>;
//     using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

// private:
//     static constexpr auto _BUF_SIZE   = _Scary_val::_BUF_SIZE;
//     static constexpr auto _ALLOC_MASK = _Scary_val::_ALLOC_MASK;

//     // When doing _String_val operations by memcpy, we are touching:
//     //   _String_val::_Bx::_Buf (type is array of _Elem)
//     //   _String_val::_Bx::_Ptr (type is pointer)
//     //   _String_val::_Mysize   (type is size_type)
//     //   _String_val::_Myres    (type is size_type)
//     // N4810 21.1 [strings.general]/1 says _Elem must be trivial standard-layout, so memcpy is safe.
//     // We need to ask if pointer is safe to memcpy.
//     // size_type must be an unsigned integral type so memcpy is safe.
//     // We also need to disable memcpy if the user has supplied _Traits, since
//     //   they can observe traits::assign and similar.
//     static constexpr bool _Can_memcpy_val = _Is_specialization_v<_Traits, char_traits> && is_trivial_v<pointer>;
//     // This offset skips over the _Container_base members, if any
//     static constexpr size_t _Memcpy_val_offset = _Size_after_ebco_v<_Container_base>;
//     static constexpr size_t _Memcpy_val_size   = sizeof(_Scary_val) - _Memcpy_val_offset;

//     template <class _Iter>
//     using _Is_elem_cptr = bool_constant<_Is_any_of_v<_Iter, const _Elem* const, _Elem* const, const _Elem*, _Elem*>>;

// #if _HAS_CXX17
//     template <class _StringViewIsh>
//     using _Is_string_view_ish =
//         enable_if_t<conjunction_v<is_convertible<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>,
//                         negation<is_convertible<const _StringViewIsh&, const _Elem*>>>,
//             int>;
// #endif // _HAS_CXX17

// public:
//     _CONSTEXPR20 basic_string(const basic_string& _Right)
//         : _Mypair(_One_then_variadic_args_t{}, _Alty_traits::select_on_container_copy_construction(_Right._Getal())) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Construct_lv_contents(_Right);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(const basic_string& _Right, const _Alloc& _Al)
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Construct_lv_contents(_Right);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string() noexcept(is_nothrow_default_constructible_v<_Alty>)
//         : _Mypair(_Zero_then_variadic_args_t{}) {
//         _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
//         _Tidy_init();
//     }

//     _CONSTEXPR20 explicit basic_string(const _Alloc& _Al) noexcept : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
//         _Tidy_init();
//     }

//     _CONSTEXPR20 basic_string(const basic_string& _Right, const size_type _Roff, const _Alloc& _Al = _Alloc())
//         : _Mypair(_One_then_variadic_args_t{}, _Al) { // construct from _Right [_Roff, <end>)
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Right, _Roff, npos);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(
//         const basic_string& _Right, const size_type _Roff, const size_type _Count, const _Alloc& _Al = _Alloc())
//         : _Mypair(_One_then_variadic_args_t{}, _Al) { // construct from _Right [_Roff, _Roff + _Count)
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Right, _Roff, _Count);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(_In_reads_(_Count) const _Elem* const _Ptr, _CRT_GUARDOVERFLOW const size_type _Count)
//         : _Mypair(_Zero_then_variadic_args_t{}) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Ptr, _Count);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(
//         _In_reads_(_Count) const _Elem* const _Ptr, _CRT_GUARDOVERFLOW const size_type _Count, const _Alloc& _Al)
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Ptr, _Count);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(_In_z_ const _Elem* const _Ptr) : _Mypair(_Zero_then_variadic_args_t{}) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Ptr);
//         _Proxy._Release();
//     }

// #if _HAS_CXX23
//     basic_string(nullptr_t) = delete;
// #endif // _HAS_CXX23

// #if _HAS_CXX17
//     template <class _Alloc2 = _Alloc, enable_if_t<_Is_allocator<_Alloc2>::value, int> = 0>
// #endif // _HAS_CXX17
//     _CONSTEXPR20 basic_string(_In_z_ const _Elem* const _Ptr, const _Alloc& _Al)
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Ptr);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(_CRT_GUARDOVERFLOW const size_type _Count, const _Elem _Ch)
//         : _Mypair(_Zero_then_variadic_args_t{}) {
//         // construct from _Count * _Ch
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Count, _Ch);
//         _Proxy._Release();
//     }

// #if _HAS_CXX17
//     template <class _Alloc2 = _Alloc, enable_if_t<_Is_allocator<_Alloc2>::value, int> = 0>
// #endif // _HAS_CXX17
//     _CONSTEXPR20 basic_string(_CRT_GUARDOVERFLOW const size_type _Count, const _Elem _Ch, const _Alloc& _Al)
//         : _Mypair(_One_then_variadic_args_t{}, _Al) { // construct from _Count * _Ch with allocator
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Count, _Ch);
//         _Proxy._Release();
//     }

//     template <class _Iter, enable_if_t<_Is_iterator_v<_Iter>, int> = 0>
//     _CONSTEXPR20 basic_string(_Iter _First, _Iter _Last, const _Alloc& _Al = _Alloc())
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         _Adl_verify_range(_First, _Last);
//         _Construct(_Get_unwrapped(_First), _Get_unwrapped(_Last), _Iter_cat_t<_Iter>{});
//         _Proxy._Release();
//     }

//     template <class _Iter>
//     _CONSTEXPR20 void _Construct(_Iter _First, const _Iter _Last, input_iterator_tag) {
//         // initialize from [_First, _Last), input iterators
//         _Tidy_deallocate_guard<basic_string> _Guard{this};
//         for (; _First != _Last; ++_First) {
//             push_back(*_First);
//         }

//         _Guard._Target = nullptr;
//     }

//     template <class _Iter>
//     _CONSTEXPR20 void _Construct(const _Iter _First, const _Iter _Last, forward_iterator_tag) {
//         // initialize from [_First, _Last), forward iterators
//         const size_type _Count = _Convert_size<size_type>(static_cast<size_t>(_STD distance(_First, _Last)));
//         reserve(_Count);
//         _Construct(_First, _Last, input_iterator_tag{});
//     }

//     _CONSTEXPR20 void _Construct(_Elem* const _First, _Elem* const _Last, random_access_iterator_tag) {
//         // initialize from [_First, _Last), pointers
//         if (_First != _Last) {
//             assign(_First, _Convert_size<size_type>(static_cast<size_t>(_Last - _First)));
//         }
//     }

//     _CONSTEXPR20 void _Construct(const _Elem* const _First, const _Elem* const _Last, random_access_iterator_tag) {
//         // initialize from [_First, _Last), const pointers
//         if (_First != _Last) {
//             assign(_First, _Convert_size<size_type>(static_cast<size_t>(_Last - _First)));
//         }
//     }

//     _CONSTEXPR20 basic_string(basic_string&& _Right) noexcept
//         : _Mypair(_One_then_variadic_args_t{}, _STD move(_Right._Getal())) {
//         _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
//         _Take_contents(_Right);
//     }

//     _CONSTEXPR20 basic_string(basic_string&& _Right, const _Alloc& _Al) noexcept(
//         _Alty_traits::is_always_equal::value) // strengthened
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         if constexpr (!_Alty_traits::is_always_equal::value) {
//             if (_Getal() != _Right._Getal()) {
//                 _Construct_lv_contents(_Right);
//                 _Proxy._Release();
//                 return;
//             }
//         }

//         _Take_contents(_Right);
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(_String_constructor_concat_tag, const basic_string& _Source_of_al,
//         const _Elem* const _Left_ptr, const size_type _Left_size, const _Elem* const _Right_ptr,
//         const size_type _Right_size)
//         : _Mypair(
//             _One_then_variadic_args_t{}, _Alty_traits::select_on_container_copy_construction(_Source_of_al._Getal())) {
//         _STL_INTERNAL_CHECK(_Left_size <= max_size());
//         _STL_INTERNAL_CHECK(_Right_size <= max_size());
//         _STL_INTERNAL_CHECK(_Right_size <= max_size() - _Left_size);
//         const auto _New_size    = static_cast<size_type>(_Left_size + _Right_size);
//         size_type _New_capacity = _BUF_SIZE - 1;
//         auto& _My_data          = _Mypair._Myval2;
//         _Elem* _Ptr             = _My_data._Bx._Buf;
//         auto&& _Alproxy         = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _My_data); // throws

// #if _HAS_CXX20
//         const bool _Activate_large_mode = _New_capacity < _New_size || _STD is_constant_evaluated();
// #else // ^^^ _HAS_CXX20 / !_HAS_CXX20 vvv
//         const bool _Activate_large_mode = _New_capacity < _New_size;
// #endif // _HAS_CXX20

//         if (_Activate_large_mode) {
//             // we should never allocate less than _BUF_SIZE space (_New_size could be small if constant evaluated)
//             const size_type _Requested_size = (_STD max) (_New_size, _BUF_SIZE);
//             _New_capacity                   = _Calculate_growth(_Requested_size, _BUF_SIZE - 1, max_size());
//             const pointer _Fancyptr         = _Getal().allocate(_New_capacity + 1); // throws
//             _Ptr                            = _Unfancy(_Fancyptr);
//             _Construct_in_place(_My_data._Bx._Ptr, _Fancyptr);
//         }

// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to avoid UB
//             _Traits::assign(_Ptr, _New_capacity + 1, _Elem());
//         }
// #endif // _HAS_CXX20

//         _My_data._Mysize = _New_size;
//         _My_data._Myres  = _New_capacity;
//         _Traits::copy(_Ptr, _Left_ptr, _Left_size);
//         _Traits::copy(_Ptr + static_cast<ptrdiff_t>(_Left_size), _Right_ptr, _Right_size);
//         _Traits::assign(_Ptr[_New_size], _Elem());
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string(_String_constructor_concat_tag, basic_string& _Left, basic_string& _Right)
//         : _Mypair(_One_then_variadic_args_t{}, _Left._Getal()) {
//         auto& _My_data    = _Mypair._Myval2;
//         auto& _Left_data  = _Left._Mypair._Myval2;
//         auto& _Right_data = _Right._Mypair._Myval2;
//         _Left_data._Orphan_all();
//         _Right_data._Orphan_all();
//         const auto _Left_size  = _Left_data._Mysize;
//         const auto _Right_size = _Right_data._Mysize;

//         const auto _Left_capacity  = _Left_data._Myres;
//         const auto _Right_capacity = _Right_data._Myres;
//         // overflow is OK due to max_size() checks:
//         const auto _New_size     = static_cast<size_type>(_Left_size + _Right_size);
//         const bool _Fits_in_left = _Right_size <= _Left_capacity - _Left_size;
//         if (_Fits_in_left && _Right_capacity <= _Left_capacity) {
//             // take _Left's buffer, max_size() is OK because _Fits_in_left
//             _My_data._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal())); // throws, hereafter nothrow in this block
//             _Take_contents(_Left);
//             const auto _Ptr = _My_data._Myptr();
//             _Traits::copy(_Ptr + _Left_size, _Right_data._Myptr(), _Right_size + 1);
//             _My_data._Mysize = _New_size;
//             return;
//         }

//         const bool _Fits_in_right = _Left_size <= _Right_capacity - _Right_size;
//         if (_Allocators_equal(_Getal(), _Right._Getal()) && _Fits_in_right) {
//             // take _Right's buffer, max_size() is OK because _Fits_in_right
//             // At this point, we have tested:
//             // !(_Fits_in_left && _Right_capacity <= _Left_capacity) && _Fits_in_right
//             // therefore: (by De Morgan's Laws)
//             // (!_Fits_in_left || _Right_capacity > _Left_capacity) && _Fits_in_right
//             // therefore: (by the distributive property)
//             // (!_Fits_in_left && _Fits_in_right)  // implying _Right has more capacity
//             //     || (_Right_capacity > _Left_capacity && _Fits_in_right)  // tests that _Right has more capacity
//             // therefore: _Right must have more than the minimum capacity, so it must be _Large_string_engaged()
//             _STL_INTERNAL_CHECK(_Right_data._Large_string_engaged());
//             _My_data._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal())); // throws, hereafter nothrow in this block
//             _Take_contents(_Right);
//             const auto _Ptr = _Unfancy(_My_data._Bx._Ptr);
//             _Traits::move(_Ptr + _Left_size, _Ptr, _Right_size + 1);
//             _Traits::copy(_Ptr, _Left_data._Myptr(), _Left_size);
//             _My_data._Mysize = _New_size;
//             return;
//         }

//         // can't use either buffer, reallocate
//         const auto _Max = max_size();
//         if (_Max - _Left_size < _Right_size) { // check if max_size() is OK
//             _Xlen_string();
//         }

//         const auto _New_capacity = _Calculate_growth(_New_size, _BUF_SIZE - 1, _Max);
//         auto&& _Alproxy          = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _My_data); // throws
//         const pointer _Fancyptr = _Getal().allocate(_New_capacity + 1); // throws
//         // nothrow hereafter
// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to avoid UB
//             _Traits::assign(_Unfancy(_Fancyptr), _New_capacity + 1, _Elem());
//         }
// #endif // _HAS_CXX20
//         _Construct_in_place(_My_data._Bx._Ptr, _Fancyptr);
//         _My_data._Mysize = _New_size;
//         _My_data._Myres  = _New_capacity;
//         const auto _Ptr  = _Unfancy(_Fancyptr);
//         _Traits::copy(_Ptr, _Left_data._Myptr(), _Left_size);
//         _Traits::copy(_Ptr + _Left_size, _Right_data._Myptr(), _Right_size + 1);
//         _Proxy._Release();
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 explicit basic_string(const _StringViewIsh& _Right, const _Alloc& _Al = _Alloc())
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Right);
//         _Proxy._Release();
//     }

//     template <class _Ty, enable_if_t<is_convertible_v<const _Ty&, basic_string_view<_Elem, _Traits>>, int> = 0>
//     _CONSTEXPR20 basic_string(
//         const _Ty& _Right, const size_type _Roff, const size_type _Count, const _Alloc& _Al = _Alloc())
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         // construct from _Right [_Roff, _Roff + _Count) using _Al
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Right, _Roff, _Count);
//         _Proxy._Release();
//     }
// #endif // _HAS_CXX17

// #if _HAS_CXX20
//     basic_string(_String_constructor_rvalue_allocator_tag, _Alloc&& _Al)
//         : _Mypair(_One_then_variadic_args_t{}, _STD move(_Al)) {
//         // Used exclusively by basic_stringbuf
//         _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
//         _Tidy_init();
//     }
// #endif // _HAS_CXX20

// public:
// #if _HAS_CXX20
//     _NODISCARD bool _Move_assign_from_buffer(_Elem* const _Right, const size_type _Size, const size_type _Res) {
//         // Move assign from a buffer, used exclusively by basic_stringbuf; returns _Large_string_engaged()
//         _Tidy_deallocate();
//         pointer _Fancy_right = _Refancy<pointer>(_Right);
//         auto& _My_data       = _Mypair._Myval2;
//         _My_data._Mysize     = _Size;
//         _My_data._Myres      = _Res - 1;
//         if (_My_data._Large_string_engaged()) {
//             _Construct_in_place(_My_data._Bx._Ptr, _Fancy_right);
//             return true;
//         } else {
//             _Traits::copy(_My_data._Bx._Buf, _Right, _Res);
//             _My_data._Myres = _BUF_SIZE - 1;
//             return false;
//         }
//     }

//     // No instance of this type can exist where an exception may be thrown.
//     struct _Released_buffer {
//         pointer _Ptr;
//         size_type _Size;
//         size_type _Res;
//     };

//     _NODISCARD _Released_buffer _Release_to_buffer(_Alloc& _Al) {
//         // Release to a buffer, or allocate a new one if in small string mode; used exclusively by basic_stringbuf
//         _Released_buffer _Result;
//         auto& _My_data = _Mypair._Myval2;
//         _Result._Size  = _My_data._Mysize;
//         if (_My_data._Large_string_engaged()) {
//             _Result._Ptr = _My_data._Bx._Ptr;
//             _Result._Res = _My_data._Myres + 1;
//         } else {
//             // use _BUF_SIZE + 1 to avoid SSO, if the buffer is assigned back
//             _Result._Ptr = _Al.allocate(_BUF_SIZE + 1);
//             _Traits::copy(_Unfancy(_Result._Ptr), _My_data._Bx._Buf, _BUF_SIZE);
//             _Result._Res = _BUF_SIZE + 1;
//         }
//         _My_data._Orphan_all();
//         _Tidy_init();
//         return _Result;
//     }
// #endif // _HAS_CXX20

//     _CONSTEXPR20 basic_string& operator=(basic_string&& _Right) noexcept(
//         _Choose_pocma_v<_Alty> != _Pocma_values::_No_propagate_allocators) {
//         if (this == _STD addressof(_Right)) {
//             return *this;
//         }

//         auto& _Al                 = _Getal();
//         auto& _Right_al           = _Right._Getal();
//         constexpr auto _Pocma_val = _Choose_pocma_v<_Alty>;
//         if constexpr (_Pocma_val == _Pocma_values::_Propagate_allocators) {
//             if (_Al != _Right_al) {
//                 // intentionally slams into noexcept on OOM, TRANSITION, VSO-466800
//                 _Mypair._Myval2._Orphan_all();
//                 _Mypair._Myval2._Reload_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Al), _GET_PROXY_ALLOCATOR(_Alty, _Right_al));
//                 _Pocma(_Al, _Right_al);
//                 _Take_contents(_Right);
//                 return *this;
//             }
//         } else if constexpr (_Pocma_val == _Pocma_values::_No_propagate_allocators) {
//             if (_Al != _Right_al) {
//                 assign(_Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//                 return *this;
//             }
//         }

//         _Tidy_deallocate();
//         _Pocma(_Al, _Right_al);
//         _Take_contents(_Right);

//         return *this;
//     }

//     _CONSTEXPR20 basic_string& assign(basic_string&& _Right) noexcept(noexcept(*this = _STD move(_Right))) {
//         *this = _STD move(_Right);
//         return *this;
//     }

// private:
//     void _Memcpy_val_from(const basic_string& _Right) noexcept {
//         _STL_INTERNAL_CHECK(_Can_memcpy_val); // TRANSITION, if constexpr
//         const auto _My_data_mem =
//             reinterpret_cast<unsigned char*>(_STD addressof(_Mypair._Myval2)) + _Memcpy_val_offset;
//         const auto _Right_data_mem =
//             reinterpret_cast<const unsigned char*>(_STD addressof(_Right._Mypair._Myval2)) + _Memcpy_val_offset;
//         _CSTD memcpy(_My_data_mem, _Right_data_mem, _Memcpy_val_size);
//     }

//     _CONSTEXPR20 void _Take_contents(basic_string& _Right) noexcept {
//         // assign by stealing _Right's buffer
//         // pre: this != &_Right
//         // pre: allocator propagation (POCMA) from _Right, if necessary, is complete
//         // pre: *this owns no memory, iterators orphaned
//         // (note: _Buf/_Ptr/_Mysize/_Myres may be garbage init)
//         auto& _My_data    = _Mypair._Myval2;
//         auto& _Right_data = _Right._Mypair._Myval2;

//         if constexpr (_Can_memcpy_val) {
// #if _HAS_CXX20
//             if (!_STD is_constant_evaluated())
// #endif // _HAS_CXX20
//             {
// #if _ITERATOR_DEBUG_LEVEL != 0
//                 if (_Right_data._Large_string_engaged()) {
//                     // take ownership of _Right's iterators along with its buffer
//                     _Swap_proxy_and_iterators(_Right);
//                 } else {
//                     _Right_data._Orphan_all();
//                 }
// #endif // _ITERATOR_DEBUG_LEVEL != 0

//                 _Memcpy_val_from(_Right);
//                 _Right._Tidy_init();
//                 return;
//             }
//         }

//         if (_Right_data._Large_string_engaged()) { // steal buffer
//             _Construct_in_place(_My_data._Bx._Ptr, _Right_data._Bx._Ptr);
//             _Right_data._Bx._Ptr = nullptr;
//             _Swap_proxy_and_iterators(_Right);
//         } else { // copy small string buffer
//             _Traits::copy(_My_data._Bx._Buf, _Right_data._Bx._Buf, _Right_data._Mysize + 1);
//             _Right_data._Orphan_all();
//         }

//         _My_data._Mysize = _Right_data._Mysize;
//         _My_data._Myres  = _Right_data._Myres;
//         _Right._Tidy_init();
//     }

//     _CONSTEXPR20 void _Construct_lv_contents(const basic_string& _Right) {
//         // assign by copying data stored in _Right
//         // pre: this != &_Right
//         // pre: *this owns no memory, iterators orphaned (note:
//         // _Buf/_Ptr/_Mysize/_Myres may be garbage init)
//         auto& _Right_data             = _Right._Mypair._Myval2;
//         const size_type _Right_size   = _Right_data._Mysize;
//         const _Elem* const _Right_ptr = _Right_data._Myptr();
//         auto& _My_data                = _Mypair._Myval2;

// #if _HAS_CXX20
//         const bool _Stay_small = _Right_size < _BUF_SIZE && !_STD is_constant_evaluated();
// #else // ^^^ _HAS_CXX20 / !_HAS_CXX20 vvv
//         const bool _Stay_small = _Right_size < _BUF_SIZE;
// #endif // _HAS_CXX20

//         // NOTE: even if _Right is in large mode, we only go into large mode ourselves if the actual size of _Right
//         // requires it
//         if (_Stay_small) { // stay small, don't allocate
//             _Traits::copy(_My_data._Bx._Buf, _Right_ptr, _BUF_SIZE);
//             _My_data._Mysize = _Right_size;
//             _My_data._Myres  = _BUF_SIZE - 1;
//             return;
//         }

//         auto& _Al                     = _Getal();
//         const size_type _New_capacity = (_STD min) (_Right_size | _ALLOC_MASK, max_size());
//         const pointer _New_array      = _Al.allocate(_New_capacity + 1); // throws
//         _Construct_in_place(_My_data._Bx._Ptr, _New_array);

// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to avoid UB
//             _Traits::assign(_Unfancy(_New_array), _New_capacity + 1, _Elem());
//         }
// #endif // _HAS_CXX20
//         _Traits::copy(_Unfancy(_New_array), _Right_ptr, _Right_size + 1);
//         _My_data._Mysize = _Right_size;
//         _My_data._Myres  = _New_capacity;
//     }

// public:
//     _CONSTEXPR20 basic_string(initializer_list<_Elem> _Ilist, const _Alloc& _Al = allocator_type())
//         : _Mypair(_One_then_variadic_args_t{}, _Al) {
//         auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
//         _Tidy_init();
//         assign(_Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//         _Proxy._Release();
//     }

//     _CONSTEXPR20 basic_string& operator=(initializer_list<_Elem> _Ilist) {
//         return assign(_Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//     }

//     _CONSTEXPR20 basic_string& operator+=(initializer_list<_Elem> _Ilist) {
//         return append(_Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//     }

//     _CONSTEXPR20 basic_string& assign(initializer_list<_Elem> _Ilist) {
//         return assign(_Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//     }

//     _CONSTEXPR20 basic_string& append(initializer_list<_Elem> _Ilist) {
//         return append(_Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//     }

//     _CONSTEXPR20 iterator insert(const const_iterator _Where, const initializer_list<_Elem> _Ilist) {
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_Where._Getcont() == _STD addressof(_Mypair._Myval2), "string iterator incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off = static_cast<size_type>(_Unfancy(_Where._Ptr) - _Mypair._Myval2._Myptr());
//         insert(_Off, _Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//         return begin() + static_cast<difference_type>(_Off);
//     }

//     _CONSTEXPR20 basic_string& replace(
//         const const_iterator _First, const const_iterator _Last, const initializer_list<_Elem> _Ilist) {
//         // replace with initializer_list
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Offset = static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr());
//         const auto _Length = static_cast<size_type>(_Last._Ptr - _First._Ptr);
//         return replace(_Offset, _Length, _Ilist.begin(), _Convert_size<size_type>(_Ilist.size()));
//     }

//     _CONSTEXPR20 ~basic_string() noexcept {
//         _Tidy_deallocate();
// #if _ITERATOR_DEBUG_LEVEL != 0
//         auto&& _Alproxy          = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
//         const auto _To_delete    = _Mypair._Myval2._Myproxy;
//         _Mypair._Myval2._Myproxy = nullptr;
//         _Delete_plain_internal(_Alproxy, _To_delete);
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//     }

//     static constexpr auto npos{static_cast<size_type>(-1)};

// private:
//     void _Copy_assign_val_from_small(const basic_string& _Right) {
//         // TRANSITION, VSO-761321; inline into only caller when that's fixed
// #if _HAS_CXX20
//         _STL_ASSERT(!_STD is_constant_evaluated(), "SSO should be disabled in a constexpr context");
// #endif // _HAS_CXX20
//         _Tidy_deallocate();
//         if constexpr (_Can_memcpy_val) {
//             _Memcpy_val_from(_Right);
//         } else {
//             auto& _My_data    = _Mypair._Myval2;
//             auto& _Right_data = _Right._Mypair._Myval2;

//             _Traits::copy(_My_data._Bx._Buf, _Right_data._Bx._Buf, _Right_data._Mysize + 1);
//             _My_data._Mysize = _Right_data._Mysize;
//             _My_data._Myres  = _Right_data._Myres;
//         }
//     }

// public:
//     _CONSTEXPR20 basic_string& operator=(const basic_string& _Right) {
//         if (this == _STD addressof(_Right)) {
//             return *this;
//         }

//         auto& _Al             = _Getal();
//         const auto& _Right_al = _Right._Getal();
//         if constexpr (_Choose_pocca_v<_Alty>) {
//             if (_Al != _Right_al) {
//                 auto&& _Alproxy       = _GET_PROXY_ALLOCATOR(_Alty, _Al);
//                 auto&& _Right_alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Right_al);
//                 _Container_proxy_ptr<_Alty> _New_proxy(_Right_alproxy, _Leave_proxy_unbound{}); // throws

//                 if (_Right._Mypair._Myval2._Large_string_engaged()) {
//                     const auto _New_size     = _Right._Mypair._Myval2._Mysize;
//                     const auto _New_capacity = _Calculate_growth(_New_size, 0, _Right.max_size());
//                     auto _Right_al_non_const = _Right_al;
//                     const auto _New_ptr      = _Right_al_non_const.allocate(_New_capacity); // throws

// #if _HAS_CXX20
//                     if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to
//                                                         // avoid UB
//                         _Traits::assign(_Unfancy(_New_ptr), _New_size + 1, _Elem());
//                     }
// #endif // _HAS_CXX20

//                     _Traits::copy(_Unfancy(_New_ptr), _Unfancy(_Right._Mypair._Myval2._Bx._Ptr), _New_size + 1);
//                     _Tidy_deallocate();
//                     _Mypair._Myval2._Bx._Ptr = _New_ptr;
//                     _Mypair._Myval2._Mysize  = _New_size;
//                     _Mypair._Myval2._Myres   = _New_capacity;
//                 } else {
//                     _Copy_assign_val_from_small(_Right);
//                 }

//                 _Pocca(_Al, _Right_al);
//                 _New_proxy._Bind(_Alproxy, _STD addressof(_Mypair._Myval2));
//                 return *this;
//             }
//         }

//         _Pocca(_Al, _Right_al);
//         assign(_Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//         return *this;
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& operator=(const _StringViewIsh& _Right) {
//         return assign(_Right);
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& operator=(_In_z_ const _Elem* const _Ptr) {
//         return assign(_Ptr);
//     }

// #if _HAS_CXX23
//     basic_string& operator=(nullptr_t) = delete;
// #endif // _HAS_CXX23

//     _CONSTEXPR20 basic_string& operator=(const _Elem _Ch) { // assign {_Ch, _Elem()}
//         _Mypair._Myval2._Mysize = 1;
//         _Elem* const _Ptr       = _Mypair._Myval2._Myptr();
//         _Traits::assign(_Ptr[0], _Ch);
//         _Traits::assign(_Ptr[1], _Elem());
//         return *this;
//     }

//     _CONSTEXPR20 basic_string& operator+=(const basic_string& _Right) {
//         return append(_Right);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& operator+=(const _StringViewIsh& _Right) {
//         return append(_Right);
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& operator+=(_In_z_ const _Elem* const _Ptr) { // append [_Ptr, <null>)
//         return append(_Ptr);
//     }

//     _CONSTEXPR20 basic_string& operator+=(_Elem _Ch) {
//         push_back(_Ch);
//         return *this;
//     }

//     _CONSTEXPR20 basic_string& append(const basic_string& _Right) {
//         return append(_Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//     }

//     _CONSTEXPR20 basic_string& append(const basic_string& _Right, const size_type _Roff, size_type _Count = npos) {
//         // append _Right [_Roff, _Roff + _Count)
//         _Right._Mypair._Myval2._Check_offset(_Roff);
//         _Count = _Right._Mypair._Myval2._Clamp_suffix_size(_Roff, _Count);
//         return append(_Right._Mypair._Myval2._Myptr() + _Roff, _Count);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& append(const _StringViewIsh& _Right) {
//         const basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return append(_As_view.data(), _Convert_size<size_type>(_As_view.size()));
//     }

//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& append(
//         const _StringViewIsh& _Right, const size_type _Roff, const size_type _Count = npos) {
//         // append _Right [_Roff, _Roff + _Count)
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return append(_As_view.substr(_Roff, _Count));
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& append(
//         _In_reads_(_Count) const _Elem* const _Ptr, _CRT_GUARDOVERFLOW const size_type _Count) {
//         // append [_Ptr, _Ptr + _Count)
//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         if (_Count <= _Mypair._Myval2._Myres - _Old_size) {
//             _Mypair._Myval2._Mysize = _Old_size + _Count;
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Traits::move(_Old_ptr + _Old_size, _Ptr, _Count);
//             _Traits::assign(_Old_ptr[_Old_size + _Count], _Elem());
//             return *this;
//         }

//         return _Reallocate_grow_by(
//             _Count,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const _Elem* const _Ptr,
//                 const size_type _Count) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Old_size);
//                 _Traits::copy(_New_ptr + _Old_size, _Ptr, _Count);
//                 _Traits::assign(_New_ptr[_Old_size + _Count], _Elem());
//             },
//             _Ptr, _Count);
//     }

//     _CONSTEXPR20 basic_string& append(_In_z_ const _Elem* const _Ptr) { // append [_Ptr, <null>)
//         return append(_Ptr, _Convert_size<size_type>(_Traits::length(_Ptr)));
//     }

//     _CONSTEXPR20 basic_string& append(_CRT_GUARDOVERFLOW const size_type _Count, const _Elem _Ch) {
//         // append _Count * _Ch
//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         if (_Count <= _Mypair._Myval2._Myres - _Old_size) {
//             _Mypair._Myval2._Mysize = _Old_size + _Count;
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Traits::assign(_Old_ptr + _Old_size, _Count, _Ch);
//             _Traits::assign(_Old_ptr[_Old_size + _Count], _Elem());
//             return *this;
//         }

//         return _Reallocate_grow_by(
//             _Count,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const size_type _Count,
//                 const _Elem _Ch) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Old_size);
//                 _Traits::assign(_New_ptr + _Old_size, _Count, _Ch);
//                 _Traits::assign(_New_ptr[_Old_size + _Count], _Elem());
//             },
//             _Count, _Ch);
//     }

//     template <class _Iter, enable_if_t<_Is_iterator_v<_Iter>, int> = 0>
//     _CONSTEXPR20 basic_string& append(const _Iter _First, const _Iter _Last) {
//         // append [_First, _Last), input iterators
//         _Adl_verify_range(_First, _Last);
//         const auto _UFirst = _Get_unwrapped(_First);
//         const auto _ULast  = _Get_unwrapped(_Last);
//         if constexpr (_Is_elem_cptr<decltype(_UFirst)>::value) {
//             return append(_UFirst, _Convert_size<size_type>(static_cast<size_t>(_ULast - _UFirst)));
//         } else {
//             const basic_string _Right(_UFirst, _ULast, get_allocator());
//             return append(_Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//         }
//     }

//     _CONSTEXPR20 basic_string& assign(const basic_string& _Right) {
//         *this = _Right;
//         return *this;
//     }

//     _CONSTEXPR20 basic_string& assign(const basic_string& _Right, const size_type _Roff, size_type _Count = npos) {
//         // assign _Right [_Roff, _Roff + _Count)
//         _Right._Mypair._Myval2._Check_offset(_Roff);
//         _Count = _Right._Mypair._Myval2._Clamp_suffix_size(_Roff, _Count);
//         return assign(_Right._Mypair._Myval2._Myptr() + _Roff, _Count);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& assign(const _StringViewIsh& _Right) {
//         const basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return assign(_As_view.data(), _Convert_size<size_type>(_As_view.size()));
//     }

//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& assign(
//         const _StringViewIsh& _Right, const size_type _Roff, const size_type _Count = npos) {
//         // assign _Right [_Roff, _Roff + _Count)
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return assign(_As_view.substr(_Roff, _Count));
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& assign(
//         _In_reads_(_Count) const _Elem* const _Ptr, _CRT_GUARDOVERFLOW const size_type _Count) {
//         // assign [_Ptr, _Ptr + _Count)
//         if (_Count <= _Mypair._Myval2._Myres) {
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Mypair._Myval2._Mysize = _Count;
//             _Traits::move(_Old_ptr, _Ptr, _Count);
//             _Traits::assign(_Old_ptr[_Count], _Elem());
//             return *this;
//         }

//         return _Reallocate_for(
//             _Count,
//             [](_Elem* const _New_ptr, const size_type _Count, const _Elem* const _Ptr) {
//                 _Traits::copy(_New_ptr, _Ptr, _Count);
//                 _Traits::assign(_New_ptr[_Count], _Elem());
//             },
//             _Ptr);
//     }

//     _CONSTEXPR20 basic_string& assign(_In_z_ const _Elem* const _Ptr) {
//         return assign(_Ptr, _Convert_size<size_type>(_Traits::length(_Ptr)));
//     }

//     _CONSTEXPR20 basic_string& assign(_CRT_GUARDOVERFLOW const size_type _Count, const _Elem _Ch) {
//         // assign _Count * _Ch
//         if (_Count <= _Mypair._Myval2._Myres) {
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Mypair._Myval2._Mysize = _Count;
//             _Traits::assign(_Old_ptr, _Count, _Ch);
//             _Traits::assign(_Old_ptr[_Count], _Elem());
//             return *this;
//         }

//         return _Reallocate_for(
//             _Count,
//             [](_Elem* const _New_ptr, const size_type _Count, const _Elem _Ch) {
//                 _Traits::assign(_New_ptr, _Count, _Ch);
//                 _Traits::assign(_New_ptr[_Count], _Elem());
//             },
//             _Ch);
//     }

//     template <class _Iter, enable_if_t<_Is_iterator_v<_Iter>, int> = 0>
//     _CONSTEXPR20 basic_string& assign(const _Iter _First, const _Iter _Last) {
//         _Adl_verify_range(_First, _Last);
//         const auto _UFirst = _Get_unwrapped(_First);
//         const auto _ULast  = _Get_unwrapped(_Last);
//         if constexpr (_Is_elem_cptr<decltype(_UFirst)>::value) {
//             return assign(_UFirst, _Convert_size<size_type>(static_cast<size_t>(_ULast - _UFirst)));
//         } else {
//             basic_string _Right(_UFirst, _ULast, get_allocator());
//             if (_Mypair._Myval2._Myres < _Right._Mypair._Myval2._Myres) {
//                 _Mypair._Myval2._Orphan_all();
//                 _Swap_data(_Right);
//                 return *this;
//             } else {
//                 return assign(_Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//             }
//         }
//     }

//     _CONSTEXPR20 basic_string& insert(const size_type _Off, const basic_string& _Right) {
//         // insert _Right at _Off
//         return insert(_Off, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//     }

//     _CONSTEXPR20 basic_string& insert(
//         const size_type _Off, const basic_string& _Right, const size_type _Roff, size_type _Count = npos) {
//         // insert _Right [_Roff, _Roff + _Count) at _Off
//         _Right._Mypair._Myval2._Check_offset(_Roff);
//         _Count = _Right._Mypair._Myval2._Clamp_suffix_size(_Roff, _Count);
//         return insert(_Off, _Right._Mypair._Myval2._Myptr() + _Roff, _Count);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& insert(const size_type _Off, const _StringViewIsh& _Right) {
//         // insert _Right at _Off
//         const basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return insert(_Off, _As_view.data(), _Convert_size<size_type>(_As_view.size()));
//     }

//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& insert(
//         const size_type _Off, const _StringViewIsh& _Right, const size_type _Roff, const size_type _Count = npos) {
//         // insert _Right [_Roff, _Roff + _Count) at _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return insert(_Off, _As_view.substr(_Roff, _Count));
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& insert(
//         const size_type _Off, _In_reads_(_Count) const _Elem* const _Ptr, _CRT_GUARDOVERFLOW const size_type _Count) {
//         // insert [_Ptr, _Ptr + _Count) at _Off
//         _Mypair._Myval2._Check_offset(_Off);
//         const size_type _Old_size = _Mypair._Myval2._Mysize;

//         // checking for overlapping ranges is technically UB (considering string literals), so just always reallocate
//         // and copy to the new buffer if constant evaluated
// #if _HAS_CXX20
//         const bool _Check_overlap = _Count <= _Mypair._Myval2._Myres - _Old_size && !_STD is_constant_evaluated();
// #else // ^^^ _HAS_CXX20 / !_HAS_CXX20 vvv
//         const bool _Check_overlap = _Count <= _Mypair._Myval2._Myres - _Old_size;
// #endif // _HAS_CXX20

//         if (_Check_overlap) {
//             _Mypair._Myval2._Mysize = _Old_size + _Count;
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Elem* const _Insert_at = _Old_ptr + _Off;
//             // the range [_Ptr, _Ptr + _Ptr_shifted_after) is left alone by moving the suffix out,
//             // while the range [_Ptr + _Ptr_shifted_after, _Ptr + _Count) shifts down by _Count
//             size_type _Ptr_shifted_after;
//             if (_Ptr + _Count <= _Insert_at || _Ptr > _Old_ptr + _Old_size) {
//                 // inserted content is before the shifted region, or does not alias
//                 _Ptr_shifted_after = _Count; // none of _Ptr's data shifts
//             } else if (_Insert_at <= _Ptr) { // all of [_Ptr, _Ptr + _Count) shifts
//                 _Ptr_shifted_after = 0;
//             } else { // [_Ptr, _Ptr + _Count) contains _Insert_at, so only the part after _Insert_at shifts
//                 _Ptr_shifted_after = static_cast<size_type>(_Insert_at - _Ptr);
//             }

//             _Traits::move(_Insert_at + _Count, _Insert_at, _Old_size - _Off + 1); // move suffix + null down
//             _Traits::copy(_Insert_at, _Ptr, _Ptr_shifted_after);
//             _Traits::copy(
//                 _Insert_at + _Ptr_shifted_after, _Ptr + _Count + _Ptr_shifted_after, _Count - _Ptr_shifted_after);
//             return *this;
//         }

//         return _Reallocate_grow_by(
//             _Count,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const size_type _Off,
//                 const _Elem* const _Ptr, const size_type _Count) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Off);
//                 _Traits::copy(_New_ptr + _Off, _Ptr, _Count);
//                 _Traits::copy(_New_ptr + _Off + _Count, _Old_ptr + _Off, _Old_size - _Off + 1);
//             },
//             _Off, _Ptr, _Count);
//     }

//     _CONSTEXPR20 basic_string& insert(const size_type _Off, _In_z_ const _Elem* const _Ptr) {
//         // insert [_Ptr, <null>) at _Off
//         return insert(_Off, _Ptr, _Convert_size<size_type>(_Traits::length(_Ptr)));
//     }

//     _CONSTEXPR20 basic_string& insert(
//         const size_type _Off, _CRT_GUARDOVERFLOW const size_type _Count, const _Elem _Ch) {
//         // insert _Count * _Ch at _Off
//         _Mypair._Myval2._Check_offset(_Off);
//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         if (_Count <= _Mypair._Myval2._Myres - _Old_size) {
//             _Mypair._Myval2._Mysize = _Old_size + _Count;
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Elem* const _Insert_at = _Old_ptr + _Off;
//             _Traits::move(_Insert_at + _Count, _Insert_at, _Old_size - _Off + 1); // move suffix + null down
//             _Traits::assign(_Insert_at, _Count, _Ch); // fill hole
//             return *this;
//         }

//         return _Reallocate_grow_by(
//             _Count,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const size_type _Off,
//                 const size_type _Count, const _Elem _Ch) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Off);
//                 _Traits::assign(_New_ptr + _Off, _Count, _Ch);
//                 _Traits::copy(_New_ptr + _Off + _Count, _Old_ptr + _Off, _Old_size - _Off + 1);
//             },
//             _Off, _Count, _Ch);
//     }

//     _CONSTEXPR20 iterator insert(const const_iterator _Where, const _Elem _Ch) { // insert _Ch at _Where
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_Where._Getcont() == _STD addressof(_Mypair._Myval2), "string iterator incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off = static_cast<size_type>(_Unfancy(_Where._Ptr) - _Mypair._Myval2._Myptr());
//         insert(_Off, 1, _Ch);
//         return begin() + static_cast<difference_type>(_Off);
//     }

//     _CONSTEXPR20 iterator insert(
//         const const_iterator _Where, _CRT_GUARDOVERFLOW const size_type _Count, const _Elem _Ch) {
//         // insert _Count * _Elem at _Where
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_Where._Getcont() == _STD addressof(_Mypair._Myval2), "string iterator incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off = static_cast<size_type>(_Unfancy(_Where._Ptr) - _Mypair._Myval2._Myptr());
//         insert(_Off, _Count, _Ch);
//         return begin() + static_cast<difference_type>(_Off);
//     }

//     template <class _Iter, enable_if_t<_Is_iterator_v<_Iter>, int> = 0>
//     _CONSTEXPR20 iterator insert(const const_iterator _Where, const _Iter _First, const _Iter _Last) {
//         // insert [_First, _Last) at _Where, input iterators
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_Where._Getcont() == _STD addressof(_Mypair._Myval2), "string iterator incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off = static_cast<size_type>(_Unfancy(_Where._Ptr) - _Mypair._Myval2._Myptr());
//         _Adl_verify_range(_First, _Last);
//         const auto _UFirst = _Get_unwrapped(_First);
//         const auto _ULast  = _Get_unwrapped(_Last);
//         if constexpr (_Is_elem_cptr<decltype(_UFirst)>::value) {
//             insert(_Off, _UFirst, _Convert_size<size_type>(static_cast<size_t>(_ULast - _UFirst)));
//         } else {
//             const basic_string _Right(_UFirst, _ULast, get_allocator());
//             insert(_Off, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//         }

//         return begin() + static_cast<difference_type>(_Off);
//     }

//     _CONSTEXPR20 basic_string& erase(const size_type _Off = 0) { // erase elements [_Off, ...)
//         _Mypair._Myval2._Check_offset(_Off);
//         _Eos(_Off);
//         return *this;
//     }

// private:
//     _CONSTEXPR20 basic_string& _Erase_noexcept(const size_type _Off, size_type _Count) noexcept {
//         _Count                    = _Mypair._Myval2._Clamp_suffix_size(_Off, _Count);
//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         _Elem* const _My_ptr      = _Mypair._Myval2._Myptr();
//         _Elem* const _Erase_at    = _My_ptr + _Off;
//         const size_type _New_size = _Old_size - _Count;
//         _Mypair._Myval2._Mysize   = _New_size;
//         _Traits::move(_Erase_at, _Erase_at + _Count, _New_size - _Off + 1); // move suffix + null up
//         return *this;
//     }

// public:
//     _CONSTEXPR20 basic_string& erase(const size_type _Off, const size_type _Count) {
//         // erase elements [_Off, _Off + _Count)
//         _Mypair._Myval2._Check_offset(_Off);
//         return _Erase_noexcept(_Off, _Count);
//     }

//     _CONSTEXPR20 iterator erase(const const_iterator _Where) noexcept /* strengthened */ {
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_Where._Getcont() == _STD addressof(_Mypair._Myval2), "string iterator incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off = static_cast<size_type>(_Unfancy(_Where._Ptr) - _Mypair._Myval2._Myptr());
//         _Erase_noexcept(_Off, 1);
//         return begin() + static_cast<difference_type>(_Off);
//     }

//     _CONSTEXPR20 iterator erase(const const_iterator _First, const const_iterator _Last) noexcept
//     /* strengthened */ {
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off = static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr());
//         _Erase_noexcept(_Off, static_cast<size_type>(_Last._Ptr - _First._Ptr));
//         return begin() + static_cast<difference_type>(_Off);
//     }

//     _CONSTEXPR20 void clear() noexcept { // erase all
//         _Eos(0);
//     }

//     _CONSTEXPR20 basic_string& replace(const size_type _Off, const size_type _Nx, const basic_string& _Right) {
//         // replace [_Off, _Off + _Nx) with _Right
//         return replace(_Off, _Nx, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//     }

//     _CONSTEXPR20 basic_string& replace(const size_type _Off, size_type _Nx, const basic_string& _Right,
//         const size_type _Roff, size_type _Count = npos) {
//         // replace [_Off, _Off + _Nx) with _Right [_Roff, _Roff + _Count)
//         _Right._Mypair._Myval2._Check_offset(_Roff);
//         _Count = _Right._Mypair._Myval2._Clamp_suffix_size(_Roff, _Count);
//         return replace(_Off, _Nx, _Right._Mypair._Myval2._Myptr() + _Roff, _Count);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& replace(const size_type _Off, const size_type _Nx, const _StringViewIsh& _Right) {
//         // replace [_Off, _Off + _Nx) with _Right
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return replace(_Off, _Nx, _As_view.data(), _Convert_size<size_type>(_As_view.size()));
//     }

//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& replace(const size_type _Off, const size_type _Nx, const _StringViewIsh& _Right,
//         const size_type _Roff, const size_type _Count = npos) {
//         // replace [_Off, _Off + _Nx) with _Right [_Roff, _Roff + _Count)
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return replace(_Off, _Nx, _As_view.substr(_Roff, _Count));
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& replace(
//         const size_type _Off, size_type _Nx, _In_reads_(_Count) const _Elem* const _Ptr, const size_type _Count) {
//         // replace [_Off, _Off + _Nx) with [_Ptr, _Ptr + _Count)
//         _Mypair._Myval2._Check_offset(_Off);
//         _Nx = _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx);
//         if (_Nx == _Count) { // size doesn't change, so a single move does the trick
//             _Traits::move(_Mypair._Myval2._Myptr() + _Off, _Ptr, _Count);
//             return *this;
//         }

//         const size_type _Old_size    = _Mypair._Myval2._Mysize;
//         const size_type _Suffix_size = _Old_size - _Nx - _Off + 1;
//         if (_Count < _Nx) { // suffix shifts backwards; we don't have to move anything out of the way
//             _Mypair._Myval2._Mysize = _Old_size - (_Nx - _Count);
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Elem* const _Insert_at = _Old_ptr + _Off;
//             _Traits::move(_Insert_at, _Ptr, _Count);
//             _Traits::move(_Insert_at + _Count, _Insert_at + _Nx, _Suffix_size);
//             return *this;
//         }

//         const size_type _Growth = static_cast<size_type>(_Count - _Nx);

//         // checking for overlapping ranges is technically UB (considering string literals), so just always reallocate
//         // and copy to the new buffer if constant evaluated
// #if _HAS_CXX20
//         if (!_STD is_constant_evaluated())
// #endif // _HAS_CXX20
//         {
//             if (_Growth <= _Mypair._Myval2._Myres - _Old_size) { // growth fits
//                 _Mypair._Myval2._Mysize = _Old_size + _Growth;
//                 _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//                 _Elem* const _Insert_at = _Old_ptr + _Off;
//                 _Elem* const _Suffix_at = _Insert_at + _Nx;

//                 size_type _Ptr_shifted_after; // see rationale in insert
//                 if (_Ptr + _Count <= _Insert_at || _Ptr > _Old_ptr + _Old_size) {
//                     _Ptr_shifted_after = _Count;
//                 } else if (_Suffix_at <= _Ptr) {
//                     _Ptr_shifted_after = 0;
//                 } else {
//                     _Ptr_shifted_after = static_cast<size_type>(_Suffix_at - _Ptr);
//                 }

//                 _Traits::move(_Suffix_at + _Growth, _Suffix_at, _Suffix_size);
//                 // next case must be move, in case _Ptr begins before _Insert_at and contains part of the hole;
//                 // this case doesn't occur in insert because the new content must come from outside the removed
//                 // content there (because in insert there is no removed content)
//                 _Traits::move(_Insert_at, _Ptr, _Ptr_shifted_after);
//                 // the next case can be copy, because it comes from the chunk moved out of the way in the
//                 // first move, and the hole we're filling can't alias the chunk we moved out of the way
//                 _Traits::copy(
//                     _Insert_at + _Ptr_shifted_after, _Ptr + _Growth + _Ptr_shifted_after, _Count - _Ptr_shifted_after);
//                 return *this;
//             }
//         }

//         return _Reallocate_grow_by(
//             _Growth,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const size_type _Off,
//                 const size_type _Nx, const _Elem* const _Ptr, const size_type _Count) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Off);
//                 _Traits::copy(_New_ptr + _Off, _Ptr, _Count);
//                 _Traits::copy(_New_ptr + _Off + _Count, _Old_ptr + _Off + _Nx, _Old_size - _Nx - _Off + 1);
//             },
//             _Off, _Nx, _Ptr, _Count);
//     }

//     _CONSTEXPR20 basic_string& replace(const size_type _Off, const size_type _Nx, _In_z_ const _Elem* const _Ptr) {
//         // replace [_Off, _Off + _Nx) with [_Ptr, <null>)
//         return replace(_Off, _Nx, _Ptr, _Convert_size<size_type>(_Traits::length(_Ptr)));
//     }

//     _CONSTEXPR20 basic_string& replace(const size_type _Off, size_type _Nx, const size_type _Count, const _Elem _Ch) {
//         // replace [_Off, _Off + _Nx) with _Count * _Ch
//         _Mypair._Myval2._Check_offset(_Off);
//         _Nx = _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx);
//         if (_Count == _Nx) {
//             _Traits::assign(_Mypair._Myval2._Myptr() + _Off, _Count, _Ch);
//             return *this;
//         }

//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         if (_Count < _Nx || _Count - _Nx <= _Mypair._Myval2._Myres - _Old_size) {
//             // either we are shrinking, or the growth fits
//             _Mypair._Myval2._Mysize = _Old_size + _Count - _Nx; // may temporarily overflow;
//                                                                 // OK because size_type must be unsigned
//             _Elem* const _Old_ptr   = _Mypair._Myval2._Myptr();
//             _Elem* const _Insert_at = _Old_ptr + _Off;
//             _Traits::move(_Insert_at + _Count, _Insert_at + _Nx, _Old_size - _Nx - _Off + 1);
//             _Traits::assign(_Insert_at, _Count, _Ch);
//             return *this;
//         }

//         return _Reallocate_grow_by(
//             _Count - _Nx,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const size_type _Off,
//                 const size_type _Nx, const size_type _Count, const _Elem _Ch) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Off);
//                 _Traits::assign(_New_ptr + _Off, _Count, _Ch);
//                 _Traits::copy(_New_ptr + _Off + _Count, _Old_ptr + _Off + _Nx, _Old_size - _Nx - _Off + 1);
//             },
//             _Off, _Nx, _Count, _Ch);
//     }

//     _CONSTEXPR20 basic_string& replace(
//         const const_iterator _First, const const_iterator _Last, const basic_string& _Right) {
//         // replace [_First, _Last) with _Right
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         return replace(static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr()),
//             static_cast<size_type>(_Last._Ptr - _First._Ptr), _Right);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _CONSTEXPR20 basic_string& replace(
//         const const_iterator _First, const const_iterator _Last, const _StringViewIsh& _Right) {
//         // replace [_First, _Last) with _Right
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         return replace(static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr()),
//             static_cast<size_type>(_Last._Ptr - _First._Ptr), _Right);
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 basic_string& replace(const const_iterator _First, const const_iterator _Last,
//         _In_reads_(_Count) const _Elem* const _Ptr, const size_type _Count) {
//         // replace [_First, _Last) with [_Ptr, _Ptr + _Count)
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         return replace(static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr()),
//             static_cast<size_type>(_Last._Ptr - _First._Ptr), _Ptr, _Count);
//     }

//     _CONSTEXPR20 basic_string& replace(
//         const const_iterator _First, const const_iterator _Last, _In_z_ const _Elem* const _Ptr) {
//         // replace [_First, _Last) with [_Ptr, <null>)
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         return replace(static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr()),
//             static_cast<size_type>(_Last._Ptr - _First._Ptr), _Ptr);
//     }

//     _CONSTEXPR20 basic_string& replace(
//         const const_iterator _First, const const_iterator _Last, const size_type _Count, const _Elem _Ch) {
//         // replace [_First, _Last) with _Count * _Ch
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         return replace(static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr()),
//             static_cast<size_type>(_Last._Ptr - _First._Ptr), _Count, _Ch);
//     }

//     template <class _Iter, enable_if_t<_Is_iterator_v<_Iter>, int> = 0>
//     _CONSTEXPR20 basic_string& replace(
//         const const_iterator _First, const const_iterator _Last, const _Iter _First2, const _Iter _Last2) {
//         // replace [_First, _Last) with [_First2, _Last2), input iterators
//         _Adl_verify_range(_First, _Last);
// #if _ITERATOR_DEBUG_LEVEL != 0
//         _STL_VERIFY(_First._Getcont() == _STD addressof(_Mypair._Myval2), "string iterators incompatible");
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         const auto _Off    = static_cast<size_type>(_Unfancy(_First._Ptr) - _Mypair._Myval2._Myptr());
//         const auto _Length = static_cast<size_type>(_Last._Ptr - _First._Ptr);
//         _Adl_verify_range(_First2, _Last2);
//         const auto _UFirst2 = _Get_unwrapped(_First2);
//         const auto _ULast2  = _Get_unwrapped(_Last2);
//         if constexpr (_Is_elem_cptr<decltype(_UFirst2)>::value) {
//             return replace(_Off, _Length, _UFirst2, _Convert_size<size_type>(static_cast<size_t>(_ULast2 - _UFirst2)));
//         } else {
//             const basic_string _Right(_UFirst2, _ULast2, get_allocator());
//             return replace(_Off, _Length, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//         }
//     }

//     _NODISCARD _CONSTEXPR20 iterator begin() noexcept {
//         return iterator(_Refancy<pointer>(_Mypair._Myval2._Myptr()), _STD addressof(_Mypair._Myval2));
//     }

//     _NODISCARD _CONSTEXPR20 const_iterator begin() const noexcept {
//         return const_iterator(_Refancy<const_pointer>(_Mypair._Myval2._Myptr()), _STD addressof(_Mypair._Myval2));
//     }

//     _NODISCARD _CONSTEXPR20 iterator end() noexcept {
//         return iterator(
//             _Refancy<pointer>(_Mypair._Myval2._Myptr()) + static_cast<difference_type>(_Mypair._Myval2._Mysize),
//             _STD addressof(_Mypair._Myval2));
//     }

//     _NODISCARD _CONSTEXPR20 const_iterator end() const noexcept {
//         return const_iterator(
//             _Refancy<const_pointer>(_Mypair._Myval2._Myptr()) + static_cast<difference_type>(_Mypair._Myval2._Mysize),
//             _STD addressof(_Mypair._Myval2));
//     }

//     _NODISCARD _CONSTEXPR20 _Elem* _Unchecked_begin() noexcept {
//         return _Mypair._Myval2._Myptr();
//     }

//     _NODISCARD _CONSTEXPR20 const _Elem* _Unchecked_begin() const noexcept {
//         return _Mypair._Myval2._Myptr();
//     }

//     _NODISCARD _CONSTEXPR20 _Elem* _Unchecked_end() noexcept {
//         return _Mypair._Myval2._Myptr() + _Mypair._Myval2._Mysize;
//     }

//     _NODISCARD _CONSTEXPR20 const _Elem* _Unchecked_end() const noexcept {
//         return _Mypair._Myval2._Myptr() + _Mypair._Myval2._Mysize;
//     }

//     _NODISCARD _CONSTEXPR20 reverse_iterator rbegin() noexcept {
//         return reverse_iterator(end());
//     }

//     _NODISCARD _CONSTEXPR20 const_reverse_iterator rbegin() const noexcept {
//         return const_reverse_iterator(end());
//     }

//     _NODISCARD _CONSTEXPR20 reverse_iterator rend() noexcept {
//         return reverse_iterator(begin());
//     }

//     _NODISCARD _CONSTEXPR20 const_reverse_iterator rend() const noexcept {
//         return const_reverse_iterator(begin());
//     }

//     _NODISCARD _CONSTEXPR20 const_iterator cbegin() const noexcept {
//         return begin();
//     }

//     _NODISCARD _CONSTEXPR20 const_iterator cend() const noexcept {
//         return end();
//     }

//     _NODISCARD _CONSTEXPR20 const_reverse_iterator crbegin() const noexcept {
//         return rbegin();
//     }

//     _NODISCARD _CONSTEXPR20 const_reverse_iterator crend() const noexcept {
//         return rend();
//     }

//     _CONSTEXPR20 void shrink_to_fit() { // reduce capacity
//         auto& _My_data = _Mypair._Myval2;

// #if _HAS_CXX20
//         if (!_STD is_constant_evaluated())
// #endif // _HAS_CXX20
//         {
//             if (!_My_data._Large_string_engaged()) { // can't shrink from small mode
//                 return;
//             }

//             if (_My_data._Mysize < _BUF_SIZE) {
//                 _Become_small();
//                 return;
//             }
//         }

//         size_type _Target_capacity = (_STD min) (_My_data._Mysize | _ALLOC_MASK, max_size());
// #if _HAS_CXX20
//         // must allocate at least _BUF_SIZE space
//         _Target_capacity = (_STD max) (_Target_capacity, _BUF_SIZE);
// #endif // _HAS_CXX20

//         if (_Target_capacity < _My_data._Myres) { // worth shrinking, do it
//             auto& _Al              = _Getal();
//             const pointer _New_ptr = _Al.allocate(_Target_capacity + 1); // throws

// #if _HAS_CXX20
//             if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to avoid UB
//                 _Traits::assign(_Unfancy(_New_ptr), _Target_capacity + 1, _Elem());
//             }
// #endif // _HAS_CXX20

//             _My_data._Orphan_all();
//             _Traits::copy(_Unfancy(_New_ptr), _Unfancy(_My_data._Bx._Ptr), _My_data._Mysize + 1);
//             _Al.deallocate(_My_data._Bx._Ptr, _My_data._Myres + 1);
//             _My_data._Bx._Ptr = _New_ptr;
//             _My_data._Myres   = _Target_capacity;
//         }
//     }

//     _NODISCARD _CONSTEXPR20 reference at(const size_type _Off) {
//         _Mypair._Myval2._Check_offset_exclusive(_Off);
//         return _Mypair._Myval2._Myptr()[_Off];
//     }

//     _NODISCARD _CONSTEXPR20 const_reference at(const size_type _Off) const {
//         _Mypair._Myval2._Check_offset_exclusive(_Off);
//         return _Mypair._Myval2._Myptr()[_Off];
//     }

//     _NODISCARD _CONSTEXPR20 reference operator[](const size_type _Off) noexcept /* strengthened */ {
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Off <= _Mypair._Myval2._Mysize, "string subscript out of range");
// #endif // _CONTAINER_DEBUG_LEVEL > 0
//         return _Mypair._Myval2._Myptr()[_Off];
//     }

//     _NODISCARD _CONSTEXPR20 const_reference operator[](const size_type _Off) const noexcept
//     /* strengthened */ {
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Off <= _Mypair._Myval2._Mysize, "string subscript out of range");
// #endif // _CONTAINER_DEBUG_LEVEL > 0
//         return _Mypair._Myval2._Myptr()[_Off];
//     }

// #if _HAS_CXX17
//     /* implicit */ _CONSTEXPR20 operator basic_string_view<_Elem, _Traits>() const noexcept {
//         // return a string_view around *this's character-type sequence
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize};
//     }
// #endif // _HAS_CXX17

//     _CONSTEXPR20 void push_back(const _Elem _Ch) { // insert element at end
//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         if (_Old_size < _Mypair._Myval2._Myres) {
//             _Mypair._Myval2._Mysize = _Old_size + 1;
//             _Elem* const _Ptr       = _Mypair._Myval2._Myptr();
//             _Traits::assign(_Ptr[_Old_size], _Ch);
//             _Traits::assign(_Ptr[_Old_size + 1], _Elem());
//             return;
//         }

//         _Reallocate_grow_by(
//             1,
//             [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size, const _Elem _Ch) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Old_size);
//                 _Traits::assign(_New_ptr[_Old_size], _Ch);
//                 _Traits::assign(_New_ptr[_Old_size + 1], _Elem());
//             },
//             _Ch);
//     }

//     _CONSTEXPR20 void pop_back() noexcept /* strengthened */ {
//         const size_type _Old_size = _Mypair._Myval2._Mysize;
// #if _ITERATOR_DEBUG_LEVEL >= 1
//         _STL_VERIFY(_Old_size != 0, "invalid to pop_back empty string");
// #endif // _ITERATOR_DEBUG_LEVEL >= 1
//         _Eos(_Old_size - 1);
//     }

//     _NODISCARD _CONSTEXPR20 reference front() noexcept /* strengthened */ {
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Mypair._Myval2._Mysize != 0, "front() called on empty string");
// #endif // _CONTAINER_DEBUG_LEVEL > 0

//         return _Mypair._Myval2._Myptr()[0];
//     }

//     _NODISCARD _CONSTEXPR20 const_reference front() const noexcept /* strengthened */ {
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Mypair._Myval2._Mysize != 0, "front() called on empty string");
// #endif // _CONTAINER_DEBUG_LEVEL > 0

//         return _Mypair._Myval2._Myptr()[0];
//     }

//     _NODISCARD _CONSTEXPR20 reference back() noexcept /* strengthened */ {
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Mypair._Myval2._Mysize != 0, "back() called on empty string");
// #endif // _CONTAINER_DEBUG_LEVEL > 0

//         return _Mypair._Myval2._Myptr()[_Mypair._Myval2._Mysize - 1];
//     }

//     _NODISCARD _CONSTEXPR20 const_reference back() const noexcept /* strengthened */ {
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Mypair._Myval2._Mysize != 0, "back() called on empty string");
// #endif // _CONTAINER_DEBUG_LEVEL > 0

//         return _Mypair._Myval2._Myptr()[_Mypair._Myval2._Mysize - 1];
//     }

//     _NODISCARD _CONSTEXPR20 _Ret_z_ const _Elem* c_str() const noexcept {
//         return _Mypair._Myval2._Myptr();
//     }

//     _NODISCARD _CONSTEXPR20 _Ret_z_ const _Elem* data() const noexcept {
//         return _Mypair._Myval2._Myptr();
//     }

// #if _HAS_CXX17
//     _NODISCARD _CONSTEXPR20 _Ret_z_ _Elem* data() noexcept {
//         return _Mypair._Myval2._Myptr();
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type length() const noexcept {
//         return _Mypair._Myval2._Mysize;
//     }

//     _NODISCARD _CONSTEXPR20 size_type size() const noexcept {
//         return _Mypair._Myval2._Mysize;
//     }

//     _NODISCARD _CONSTEXPR20 size_type max_size() const noexcept {
//         const size_type _Alloc_max   = _Alty_traits::max_size(_Getal());
//         const size_type _Storage_max = // can always store small string
//             (_STD max) (_Alloc_max, static_cast<size_type>(_BUF_SIZE));
//         return (_STD min) (static_cast<size_type>((numeric_limits<difference_type>::max) ()),
//             _Storage_max - 1 // -1 is for null terminator and/or npos
//         );
//     }

//     _CONSTEXPR20 void resize(_CRT_GUARDOVERFLOW const size_type _New_size, const _Elem _Ch = _Elem()) {
//         // determine new length, padding with _Ch elements as needed
//         const size_type _Old_size = size();
//         if (_New_size <= _Old_size) {
//             _Eos(_New_size);
//         } else {
//             append(_New_size - _Old_size, _Ch);
//         }
//     }

// #if _HAS_CXX23
//     template <class _Operation>
//     constexpr void resize_and_overwrite(_CRT_GUARDOVERFLOW const size_type _New_size, _Operation _Op) {
//         if (_Mypair._Myval2._Myres < _New_size) {
//             _Reallocate_grow_by(_New_size - _Mypair._Myval2._Mysize,
//                 [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size) {
//                     _Traits::copy(_New_ptr, _Old_ptr, _Old_size + 1);
//                 });
//         }

//         const auto _Result_size = _STD move(_Op)(_Mypair._Myval2._Myptr(), _New_size);
// #if _CONTAINER_DEBUG_LEVEL > 0
//         _STL_VERIFY(_Result_size >= 0, "the returned size can't be smaller than 0");
//         _STL_VERIFY(_Result_size <= _New_size, "the returned size can't be greater than the passed size");
// #endif // _CONTAINER_DEBUG_LEVEL > 0
//         _Eos(_Result_size);
//     }
// #endif // _HAS_CXX23

//     _NODISCARD _CONSTEXPR20 size_type capacity() const noexcept {
//         return _Mypair._Myval2._Myres;
//     }

// #if _HAS_CXX20
//     constexpr void reserve(_CRT_GUARDOVERFLOW const size_type _Newcap) {
//         // determine new minimum length of allocated storage
//         if (_Mypair._Myval2._Myres >= _Newcap) { // requested capacity is not larger than current capacity, ignore
//             return; // nothing to do
//         }

//         const size_type _Old_size = _Mypair._Myval2._Mysize;
//         _Reallocate_grow_by(
//             _Newcap - _Old_size, [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size) {
//                 _Traits::copy(_New_ptr, _Old_ptr, _Old_size + 1);
//             });

//         _Mypair._Myval2._Mysize = _Old_size;
//     }

//     _CXX20_DEPRECATE_STRING_RESERVE_WITHOUT_ARGUMENT void reserve() {
//         if (_Mypair._Myval2._Mysize == 0 && _Mypair._Myval2._Large_string_engaged()) {
//             _Become_small();
//         }
//     }
// #else // _HAS_CXX20
//     void reserve(_CRT_GUARDOVERFLOW const size_type _Newcap = 0) { // determine new minimum length of allocated storage
//         if (_Mypair._Myval2._Mysize > _Newcap) { // requested capacity is not large enough for current size, ignore
//             return; // nothing to do
//         }

//         if (_Mypair._Myval2._Myres == _Newcap) { // we're already at the requested capacity
//             return; // nothing to do
//         }

//         if (_Mypair._Myval2._Myres < _Newcap) { // reallocate to grow
//             const size_type _Old_size = _Mypair._Myval2._Mysize;
//             _Reallocate_grow_by(
//                 _Newcap - _Old_size, [](_Elem* const _New_ptr, const _Elem* const _Old_ptr, const size_type _Old_size) {
//                     _Traits::copy(_New_ptr, _Old_ptr, _Old_size + 1);
//                 });

//             _Mypair._Myval2._Mysize = _Old_size;
//             return;
//         }

//         if (_BUF_SIZE > _Newcap && _Mypair._Myval2._Large_string_engaged()) {
//             // deallocate everything; switch back to "small" mode
//             _Become_small();
//             return;
//         }

//         // ignore requests to reserve to [_BUF_SIZE, _Myres)
//     }
// #endif // _HAS_CXX20

//     _NODISCARD _CONSTEXPR20 bool empty() const noexcept {
//         return _Mypair._Myval2._Mysize == 0;
//     }

//     _CONSTEXPR20 size_type copy(
//         _Out_writes_(_Count) _Elem* const _Ptr, size_type _Count, const size_type _Off = 0) const {
//         // copy [_Off, _Off + _Count) to [_Ptr, _Ptr + _Count)
//         _Mypair._Myval2._Check_offset(_Off);
//         _Count = _Mypair._Myval2._Clamp_suffix_size(_Off, _Count);
//         _Traits::copy(_Ptr, _Mypair._Myval2._Myptr() + _Off, _Count);
//         return _Count;
//     }

//     _CONSTEXPR20 _Pre_satisfies_(_Dest_size >= _Count) size_type
//         _Copy_s(_Out_writes_all_(_Dest_size) _Elem* const _Dest, const size_type _Dest_size, size_type _Count,
//             const size_type _Off = 0) const {
//         // copy [_Off, _Off + _Count) to [_Dest, _Dest + _Dest_size)
//         _Mypair._Myval2._Check_offset(_Off);
//         _Count = _Mypair._Myval2._Clamp_suffix_size(_Off, _Count);
//         _Traits::_Copy_s(_Dest, _Dest_size, _Mypair._Myval2._Myptr() + _Off, _Count);
//         return _Count;
//     }

//     void _Swap_bx_large_with_small(_Scary_val& _Starts_large, _Scary_val& _Starts_small) {
//         // exchange a string in large mode with one in small mode
//         // (not _CONSTEXPR20; SSO should be disabled in a constexpr context)

//         const pointer _Ptr = _Starts_large._Bx._Ptr;
//         _Destroy_in_place(_Starts_large._Bx._Ptr);
//         _Traits::copy(_Starts_large._Bx._Buf, _Starts_small._Bx._Buf, _BUF_SIZE);
//         _Construct_in_place(_Starts_small._Bx._Ptr, _Ptr);
//     }

//     _CONSTEXPR20 void _Swap_data(basic_string& _Right) {
//         auto& _My_data    = _Mypair._Myval2;
//         auto& _Right_data = _Right._Mypair._Myval2;

//         if constexpr (_Can_memcpy_val) {
// #if _HAS_CXX20
//             if (!_STD is_constant_evaluated())
// #endif // _HAS_CXX20
//             {
//                 const auto _My_data_mem =
//                     reinterpret_cast<unsigned char*>(_STD addressof(_My_data)) + _Memcpy_val_offset;
//                 const auto _Right_data_mem =
//                     reinterpret_cast<unsigned char*>(_STD addressof(_Right_data)) + _Memcpy_val_offset;
//                 unsigned char _Temp_mem[_Memcpy_val_size];
//                 _CSTD memcpy(_Temp_mem, _My_data_mem, _Memcpy_val_size);
//                 _CSTD memcpy(_My_data_mem, _Right_data_mem, _Memcpy_val_size);
//                 _CSTD memcpy(_Right_data_mem, _Temp_mem, _Memcpy_val_size);
//                 return;
//             }
//         }

//         const bool _My_large    = _My_data._Large_string_engaged();
//         const bool _Right_large = _Right_data._Large_string_engaged();
//         if (_My_large) {
//             if (_Right_large) { // swap buffers, iterators preserved
//                 _Swap_adl(_My_data._Bx._Ptr, _Right_data._Bx._Ptr);
//             } else { // swap large with small
//                 _Swap_bx_large_with_small(_My_data, _Right_data);
//             }
//         } else {
//             if (_Right_large) { // swap small with large
//                 _Swap_bx_large_with_small(_Right_data, _My_data);
//             } else {
//                 _Elem _Temp_buf[_BUF_SIZE];
//                 _Traits::copy(_Temp_buf, _My_data._Bx._Buf, _BUF_SIZE);
//                 _Traits::copy(_My_data._Bx._Buf, _Right_data._Bx._Buf, _BUF_SIZE);
//                 _Traits::copy(_Right_data._Bx._Buf, _Temp_buf, _BUF_SIZE);
//             }
//         }

//         _STD swap(_My_data._Mysize, _Right_data._Mysize);
//         _STD swap(_My_data._Myres, _Right_data._Myres);
//     }

//     _CONSTEXPR20 void swap(basic_string& _Right) noexcept /* strengthened */ {
//         if (this != _STD addressof(_Right)) {
//             _Pocs(_Getal(), _Right._Getal());

// #if _ITERATOR_DEBUG_LEVEL != 0
//             const bool _My_large    = _Mypair._Myval2._Large_string_engaged();
//             const bool _Right_large = _Right._Mypair._Myval2._Large_string_engaged();
//             if (!_My_large) {
//                 _Mypair._Myval2._Orphan_all();
//             }

//             if (!_Right_large) {
//                 _Right._Mypair._Myval2._Orphan_all();
//             }

//             if (_My_large || _Right_large) {
//                 _Mypair._Myval2._Swap_proxy_and_iterators(_Right._Mypair._Myval2);
//             }
// #endif // _ITERATOR_DEBUG_LEVEL != 0
//         }

//         _Swap_data(_Right);
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 size_type find(const _StringViewIsh& _Right, const size_type _Off = 0) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // look for _Right beginning at or after _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return static_cast<size_type>(_Traits_find<_Traits>(
//             _Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _As_view.data(), _As_view.size()));
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type find(const basic_string& _Right, const size_type _Off = 0) const noexcept {
//         // look for _Right beginning at or after _Off
//         return static_cast<size_type>(_Traits_find<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off,
//             _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find(_In_reads_(_Count) const _Elem* const _Ptr, const size_type _Off,
//         const size_type _Count) const noexcept /* strengthened */ {
//         // look for [_Ptr, _Ptr + _Count) beginning at or after _Off
//         return static_cast<size_type>(
//             _Traits_find<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ptr, _Count));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find(_In_z_ const _Elem* const _Ptr, const size_type _Off = 0) const noexcept
//     /* strengthened */ {
//         // look for [_Ptr, <null>) beginning at or after _Off
//         return static_cast<size_type>(_Traits_find<_Traits>(
//             _Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ptr, _Traits::length(_Ptr)));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find(const _Elem _Ch, const size_type _Off = 0) const noexcept {
//         // look for _Ch at or after _Off
//         return static_cast<size_type>(
//             _Traits_find_ch<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ch));
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 size_type rfind(const _StringViewIsh& _Right, const size_type _Off = npos) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // look for _Right beginning before _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return static_cast<size_type>(_Traits_rfind<_Traits>(
//             _Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _As_view.data(), _As_view.size()));
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type rfind(const basic_string& _Right, const size_type _Off = npos) const noexcept {
//         // look for _Right beginning before _Off
//         return static_cast<size_type>(_Traits_rfind<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off,
//             _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize));
//     }

//     _NODISCARD _CONSTEXPR20 size_type rfind(_In_reads_(_Count) const _Elem* const _Ptr, const size_type _Off,
//         const size_type _Count) const noexcept /* strengthened */ {
//         // look for [_Ptr, _Ptr + _Count) beginning before _Off
//         return static_cast<size_type>(
//             _Traits_rfind<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ptr, _Count));
//     }

//     _NODISCARD _CONSTEXPR20 size_type rfind(_In_z_ const _Elem* const _Ptr, const size_type _Off = npos) const noexcept
//     /* strengthened */ {
//         // look for [_Ptr, <null>) beginning before _Off
//         return static_cast<size_type>(_Traits_rfind<_Traits>(
//             _Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ptr, _Traits::length(_Ptr)));
//     }

//     _NODISCARD _CONSTEXPR20 size_type rfind(const _Elem _Ch, const size_type _Off = npos) const noexcept {
//         // look for _Ch before _Off
//         return static_cast<size_type>(
//             _Traits_rfind_ch<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ch));
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 size_type find_first_of(const _StringViewIsh& _Right, const size_type _Off = 0) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // look for one of _Right at or after _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return static_cast<size_type>(_Traits_find_first_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _As_view.data(), _As_view.size(), _Is_specialization<_Traits, char_traits>{}));
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type find_first_of(
//         const basic_string& _Right, const size_type _Off = 0) const noexcept {
//         // look for one of _Right at or after _Off
//         return static_cast<size_type>(_Traits_find_first_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize,
//             _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_first_of(_In_reads_(_Count) const _Elem* const _Ptr, const size_type _Off,
//         const size_type _Count) const noexcept /* strengthened */ {
//         // look for one of [_Ptr, _Ptr + _Count) at or after _Off
//         return static_cast<size_type>(_Traits_find_first_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _Ptr, _Count, _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_first_of(
//         _In_z_ const _Elem* const _Ptr, const size_type _Off = 0) const noexcept /* strengthened */ {
//         // look for one of [_Ptr, <null>) at or after _Off
//         return static_cast<size_type>(_Traits_find_first_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _Ptr, _Traits::length(_Ptr), _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_first_of(const _Elem _Ch, const size_type _Off = 0) const noexcept {
//         // look for _Ch at or after _Off
//         return static_cast<size_type>(
//             _Traits_find_ch<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ch));
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 size_type find_last_of(const _StringViewIsh& _Right, const size_type _Off = npos) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // look for one of _Right before _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return static_cast<size_type>(_Traits_find_last_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _As_view.data(), _As_view.size(), _Is_specialization<_Traits, char_traits>{}));
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type find_last_of(const basic_string& _Right, size_type _Off = npos) const noexcept {
//         // look for one of _Right before _Off
//         return static_cast<size_type>(_Traits_find_last_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize,
//             _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_last_of(_In_reads_(_Count) const _Elem* const _Ptr, const size_type _Off,
//         const size_type _Count) const noexcept /* strengthened */ {
//         // look for one of [_Ptr, _Ptr + _Count) before _Off
//         return static_cast<size_type>(_Traits_find_last_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _Ptr, _Count, _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_last_of(
//         _In_z_ const _Elem* const _Ptr, const size_type _Off = npos) const noexcept /* strengthened */ {
//         // look for one of [_Ptr, <null>) before _Off
//         return static_cast<size_type>(_Traits_find_last_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Off, _Ptr, _Traits::length(_Ptr), _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_last_of(const _Elem _Ch, const size_type _Off = npos) const noexcept {
//         // look for _Ch before _Off
//         return static_cast<size_type>(
//             _Traits_rfind_ch<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ch));
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 size_type find_first_not_of(const _StringViewIsh& _Right, const size_type _Off = 0) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // look for none of _Right at or after _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return static_cast<size_type>(
//             _Traits_find_first_not_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _As_view.data(),
//                 _As_view.size(), _Is_specialization<_Traits, char_traits>{}));
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type find_first_not_of(
//         const basic_string& _Right, const size_type _Off = 0) const noexcept {
//         // look for none of _Right at or after _Off
//         return static_cast<size_type>(_Traits_find_first_not_of<_Traits>(_Mypair._Myval2._Myptr(),
//             _Mypair._Myval2._Mysize, _Off, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize,
//             _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_first_not_of(_In_reads_(_Count) const _Elem* const _Ptr,
//         const size_type _Off, const size_type _Count) const noexcept /* strengthened */ {
//         // look for none of [_Ptr, _Ptr + _Count) at or after _Off
//         return static_cast<size_type>(_Traits_find_first_not_of<_Traits>(_Mypair._Myval2._Myptr(),
//             _Mypair._Myval2._Mysize, _Off, _Ptr, _Count, _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_first_not_of(
//         _In_z_ const _Elem* const _Ptr, size_type _Off = 0) const noexcept /* strengthened */ {
//         // look for one of [_Ptr, <null>) at or after _Off
//         return static_cast<size_type>(_Traits_find_first_not_of<_Traits>(_Mypair._Myval2._Myptr(),
//             _Mypair._Myval2._Mysize, _Off, _Ptr, _Traits::length(_Ptr), _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_first_not_of(const _Elem _Ch, const size_type _Off = 0) const noexcept {
//         // look for non-_Ch at or after _Off
//         return static_cast<size_type>(
//             _Traits_find_not_ch<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ch));
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 size_type find_last_not_of(const _StringViewIsh& _Right, const size_type _Off = npos) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // look for none of _Right before _Off
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return static_cast<size_type>(
//             _Traits_find_last_not_of<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _As_view.data(),
//                 _As_view.size(), _Is_specialization<_Traits, char_traits>{}));
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 size_type find_last_not_of(
//         const basic_string& _Right, const size_type _Off = npos) const noexcept {
//         // look for none of _Right before _Off
//         return static_cast<size_type>(_Traits_find_last_not_of<_Traits>(_Mypair._Myval2._Myptr(),
//             _Mypair._Myval2._Mysize, _Off, _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize,
//             _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_last_not_of(_In_reads_(_Count) const _Elem* const _Ptr, const size_type _Off,
//         const size_type _Count) const noexcept /* strengthened */ {
//         // look for none of [_Ptr, _Ptr + _Count) before _Off
//         return static_cast<size_type>(_Traits_find_last_not_of<_Traits>(_Mypair._Myval2._Myptr(),
//             _Mypair._Myval2._Mysize, _Off, _Ptr, _Count, _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_last_not_of(
//         _In_z_ const _Elem* const _Ptr, const size_type _Off = npos) const noexcept /* strengthened */ {
//         // look for none of [_Ptr, <null>) before _Off
//         return static_cast<size_type>(_Traits_find_last_not_of<_Traits>(_Mypair._Myval2._Myptr(),
//             _Mypair._Myval2._Mysize, _Off, _Ptr, _Traits::length(_Ptr), _Is_specialization<_Traits, char_traits>{}));
//     }

//     _NODISCARD _CONSTEXPR20 size_type find_last_not_of(const _Elem _Ch, const size_type _Off = npos) const noexcept {
//         // look for non-_Ch before _Off
//         return static_cast<size_type>(
//             _Traits_rfind_not_ch<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Off, _Ch));
//     }

// #if _HAS_CXX17
//     _NODISCARD bool _Starts_with(const basic_string_view<_Elem, _Traits> _Right) const noexcept {
//         // Used exclusively by filesystem
//         return basic_string_view<_Elem, _Traits>(*this)._Starts_with(_Right);
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 basic_string substr(const size_type _Off = 0, const size_type _Count = npos) const {
//         // return [_Off, _Off + _Count) as new string
//         return basic_string(*this, _Off, _Count, get_allocator());
//     }

//     _CONSTEXPR20 bool _Equal(const basic_string& _Right) const noexcept {
//         // compare [0, size()) with _Right for equality
//         return _Traits_equal<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//     }

//     _CONSTEXPR20 bool _Equal(_In_z_ const _Elem* const _Ptr) const noexcept {
//         // compare [0, size()) with _Ptr for equality
//         return _Traits_equal<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Ptr, _Traits::length(_Ptr));
//     }

// #if _HAS_CXX17
//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 int compare(const _StringViewIsh& _Right) const
//         noexcept(_Is_nothrow_convertible_v<const _StringViewIsh&, basic_string_view<_Elem, _Traits>>) {
//         // compare [0, size()) with _Right
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         return _Traits_compare<_Traits>(
//             _Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _As_view.data(), _As_view.size());
//     }

//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 int compare(const size_type _Off, const size_type _Nx, const _StringViewIsh& _Right) const {
//         // compare [_Off, _Off + _Nx) with _Right
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         _Mypair._Myval2._Check_offset(_Off);
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr() + _Off, _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx),
//             _As_view.data(), _As_view.size());
//     }

//     template <class _StringViewIsh, _Is_string_view_ish<_StringViewIsh> = 0>
//     _NODISCARD _CONSTEXPR20 int compare(const size_type _Off, const size_type _Nx, const _StringViewIsh& _Right,
//         const size_type _Roff, const size_type _Count = npos) const {
//         // compare [_Off, _Off + _Nx) with _Right [_Roff, _Roff + _Count)
//         basic_string_view<_Elem, _Traits> _As_view = _Right;
//         _Mypair._Myval2._Check_offset(_Off);
//         const auto _With_substr = _As_view.substr(_Roff, _Count);
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr() + _Off, _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx),
//             _With_substr.data(), _With_substr.size());
//     }
// #endif // _HAS_CXX17

//     _NODISCARD _CONSTEXPR20 int compare(const basic_string& _Right) const noexcept {
//         // compare [0, size()) with _Right
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize,
//             _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//     }

//     _NODISCARD _CONSTEXPR20 int compare(size_type _Off, size_type _Nx, const basic_string& _Right) const {
//         // compare [_Off, _Off + _Nx) with _Right
//         _Mypair._Myval2._Check_offset(_Off);
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr() + _Off, _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx),
//             _Right._Mypair._Myval2._Myptr(), _Right._Mypair._Myval2._Mysize);
//     }

//     _NODISCARD _CONSTEXPR20 int compare(const size_type _Off, const size_type _Nx, const basic_string& _Right,
//         const size_type _Roff, const size_type _Count = npos) const {
//         // compare [_Off, _Off + _Nx) with _Right [_Roff, _Roff + _Count)
//         _Mypair._Myval2._Check_offset(_Off);
//         _Right._Mypair._Myval2._Check_offset(_Roff);
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr() + _Off, _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx),
//             _Right._Mypair._Myval2._Myptr() + _Roff, _Right._Mypair._Myval2._Clamp_suffix_size(_Roff, _Count));
//     }

//     _NODISCARD _CONSTEXPR20 int compare(_In_z_ const _Elem* const _Ptr) const noexcept /* strengthened */ {
//         // compare [0, size()) with [_Ptr, <null>)
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize, _Ptr, _Traits::length(_Ptr));
//     }

//     _NODISCARD _CONSTEXPR20 int compare(
//         const size_type _Off, const size_type _Nx, _In_z_ const _Elem* const _Ptr) const {
//         // compare [_Off, _Off + _Nx) with [_Ptr, <null>)
//         _Mypair._Myval2._Check_offset(_Off);
//         return _Traits_compare<_Traits>(_Mypair._Myval2._Myptr() + _Off, _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx),
//             _Ptr, _Traits::length(_Ptr));
//     }

//     _NODISCARD _CONSTEXPR20 int compare(const size_type _Off, const size_type _Nx,
//         _In_reads_(_Count) const _Elem* const _Ptr, const size_type _Count) const {
//         // compare [_Off, _Off + _Nx) with [_Ptr, _Ptr + _Count)
//         _Mypair._Myval2._Check_offset(_Off);
//         return _Traits_compare<_Traits>(
//             _Mypair._Myval2._Myptr() + _Off, _Mypair._Myval2._Clamp_suffix_size(_Off, _Nx), _Ptr, _Count);
//     }

// #if _HAS_CXX20
//     _NODISCARD constexpr bool starts_with(const basic_string_view<_Elem, _Traits> _Right) const noexcept {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.starts_with(_Right);
//     }

//     _NODISCARD constexpr bool starts_with(const _Elem _Right) const noexcept {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.starts_with(_Right);
//     }

//     _NODISCARD constexpr bool starts_with(const _Elem* const _Right) const noexcept /* strengthened */ {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.starts_with(_Right);
//     }

//     _NODISCARD constexpr bool ends_with(const basic_string_view<_Elem, _Traits> _Right) const noexcept {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.ends_with(_Right);
//     }

//     _NODISCARD constexpr bool ends_with(const _Elem _Right) const noexcept {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.ends_with(_Right);
//     }

//     _NODISCARD constexpr bool ends_with(const _Elem* const _Right) const noexcept /* strengthened */ {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.ends_with(_Right);
//     }
// #endif // _HAS_CXX20

// #if _HAS_CXX23
//     _NODISCARD constexpr bool contains(const basic_string_view<_Elem, _Traits> _Right) const noexcept {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.contains(_Right);
//     }

//     _NODISCARD constexpr bool contains(const _Elem _Right) const noexcept {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.contains(_Right);
//     }

//     _NODISCARD constexpr bool contains(const _Elem* const _Right) const noexcept /* strengthened */ {
//         return basic_string_view<_Elem, _Traits>{_Mypair._Myval2._Myptr(), _Mypair._Myval2._Mysize}.contains(_Right);
//     }
// #endif // _HAS_CXX23

//     _NODISCARD _CONSTEXPR20 allocator_type get_allocator() const noexcept {
//         return static_cast<allocator_type>(_Getal());
//     }

// private:
//     _NODISCARD static _CONSTEXPR20 size_type _Calculate_growth(
//         const size_type _Requested, const size_type _Old, const size_type _Max) noexcept {
//         const size_type _Masked = _Requested | _ALLOC_MASK;
//         if (_Masked > _Max) { // the mask overflows, settle for max_size()
//             return _Max;
//         }

//         if (_Old > _Max - _Old / 2) { // similarly, geometric overflows
//             return _Max;
//         }

//         return (_STD max) (_Masked, _Old + _Old / 2);
//     }

//     _NODISCARD _CONSTEXPR20 size_type _Calculate_growth(const size_type _Requested) const noexcept {
//         return _Calculate_growth(_Requested, _Mypair._Myval2._Myres, max_size());
//     }

//     template <class _Fty, class... _ArgTys>
//     _CONSTEXPR20 basic_string& _Reallocate_for(const size_type _New_size, _Fty _Fn, _ArgTys... _Args) {
//         // reallocate to store exactly _New_size elements, new buffer prepared by
//         // _Fn(_New_ptr, _New_size, _Args...)
//         if (_New_size > max_size()) {
//             _Xlen_string(); // result too long
//         }

//         const size_type _Old_capacity = _Mypair._Myval2._Myres;
//         const size_type _New_capacity = _Calculate_growth(_New_size);
//         auto& _Al                     = _Getal();
//         const pointer _New_ptr        = _Al.allocate(_New_capacity + 1); // throws

// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to avoid UB
//             _Traits::assign(_Unfancy(_New_ptr), _New_capacity + 1, _Elem());
//         }
// #endif // _HAS_CXX20
//         _Mypair._Myval2._Orphan_all();
//         _Mypair._Myval2._Mysize = _New_size;
//         _Mypair._Myval2._Myres  = _New_capacity;
//         _Fn(_Unfancy(_New_ptr), _New_size, _Args...);
//         if (_BUF_SIZE <= _Old_capacity) {
//             _Al.deallocate(_Mypair._Myval2._Bx._Ptr, _Old_capacity + 1);
//             _Mypair._Myval2._Bx._Ptr = _New_ptr;
//         } else {
//             _Construct_in_place(_Mypair._Myval2._Bx._Ptr, _New_ptr);
//         }

//         return *this;
//     }

//     template <class _Fty, class... _ArgTys>
//     _CONSTEXPR20 basic_string& _Reallocate_grow_by(const size_type _Size_increase, _Fty _Fn, _ArgTys... _Args) {
//         // reallocate to increase size by _Size_increase elements, new buffer prepared by
//         // _Fn(_New_ptr, _Old_ptr, _Old_size, _Args...)
//         auto& _My_data            = _Mypair._Myval2;
//         const size_type _Old_size = _My_data._Mysize;
//         if (max_size() - _Old_size < _Size_increase) {
//             _Xlen_string(); // result too long
//         }

//         const size_type _New_size     = _Old_size + _Size_increase;
//         const size_type _Old_capacity = _My_data._Myres;
//         const size_type _New_capacity = _Calculate_growth(_New_size);
//         auto& _Al                     = _Getal();
//         const pointer _New_ptr        = _Al.allocate(_New_capacity + 1); // throws

// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) { // Begin the lifetimes of the objects before copying to avoid UB
//             _Traits::assign(_Unfancy(_New_ptr), _New_capacity + 1, _Elem());
//         }
// #endif // _HAS_CXX20
//         _My_data._Orphan_all();
//         _My_data._Mysize      = _New_size;
//         _My_data._Myres       = _New_capacity;
//         _Elem* const _Raw_new = _Unfancy(_New_ptr);
//         if (_BUF_SIZE <= _Old_capacity) {
//             const pointer _Old_ptr = _My_data._Bx._Ptr;
//             _Fn(_Raw_new, _Unfancy(_Old_ptr), _Old_size, _Args...);
//             _Al.deallocate(_Old_ptr, _Old_capacity + 1);
//             _My_data._Bx._Ptr = _New_ptr;
//         } else {
//             _Fn(_Raw_new, _My_data._Bx._Buf, _Old_size, _Args...);
//             _Construct_in_place(_My_data._Bx._Ptr, _New_ptr);
//         }

//         return *this;
//     }

//     void _Become_small() {
//         // release any held storage and return to small string mode
//         // pre: *this is in large string mode
//         // pre: this is small enough to return to small string mode
//         // (not _CONSTEXPR20; SSO should be disabled in a constexpr context)

//         _Mypair._Myval2._Orphan_all();
//         const pointer _Ptr = _Mypair._Myval2._Bx._Ptr;
//         auto& _Al          = _Getal();
//         _Destroy_in_place(_Mypair._Myval2._Bx._Ptr);
//         _Traits::copy(_Mypair._Myval2._Bx._Buf, _Unfancy(_Ptr), _Mypair._Myval2._Mysize + 1);
//         _Al.deallocate(_Ptr, _Mypair._Myval2._Myres + 1);
//         _Mypair._Myval2._Myres = _BUF_SIZE - 1;
//     }

//     _CONSTEXPR20 void _Eos(const size_type _New_size) { // set new length and null terminator
//         _Traits::assign(_Mypair._Myval2._Myptr()[_Mypair._Myval2._Mysize = _New_size], _Elem());
//     }

//     _CONSTEXPR20 void _Tidy_init() noexcept { // initialize basic_string data members
//         auto& _My_data   = _Mypair._Myval2;
//         _My_data._Mysize = 0;

// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) {
//             _My_data._Myres        = _BUF_SIZE; // SSO disabled in constexpr context
//             auto& _Al              = _Getal();
//             const pointer _New_ptr = _Al.allocate(_BUF_SIZE + 1); // throws
//             _My_data._Bx._Ptr      = _New_ptr;

//             _Elem* const _Raw_new = _Unfancy(_New_ptr);
//             _Traits::assign(_Raw_new, _BUF_SIZE + 1, _Elem());
//         } else
// #endif // _HAS_CXX20
//         {
//             _My_data._Myres = _BUF_SIZE - 1;
//             // the _Traits::assign is last so the codegen doesn't think the char write can alias this
//             _Traits::assign(_My_data._Bx._Buf[0], _Elem());
//         }
//     }

//     _CONSTEXPR20 void _Tidy_deallocate() noexcept { // initialize buffer, deallocating any storage
//         _Mypair._Myval2._Orphan_all();
//         if (_Mypair._Myval2._Large_string_engaged()) {
//             const pointer _Ptr = _Mypair._Myval2._Bx._Ptr;
//             auto& _Al          = _Getal();
//             _Destroy_in_place(_Mypair._Myval2._Bx._Ptr);
//             _Al.deallocate(_Ptr, _Mypair._Myval2._Myres + 1);
//         }

// #if _HAS_CXX20
//         if (_STD is_constant_evaluated()) {
//             _Mypair._Myval2._Bx._Ptr = nullptr;
//             _Mypair._Myval2._Mysize  = 0;
//             _Mypair._Myval2._Myres   = 0;
//         } else
// #endif // _HAS_CXX20
//         {
//             _Mypair._Myval2._Mysize = 0;
//             _Mypair._Myval2._Myres  = _BUF_SIZE - 1;
//             // the _Traits::assign is last so the codegen doesn't think the char write can alias this
//             _Traits::assign(_Mypair._Myval2._Bx._Buf[0], _Elem());
//         }
//     }

// public:
//     _CONSTEXPR20 void _Orphan_all() noexcept { // used by filesystem::path
//         _Mypair._Myval2._Orphan_all();
//     }

// private:
//     _CONSTEXPR20 void _Swap_proxy_and_iterators(basic_string& _Right) {
//         _Mypair._Myval2._Swap_proxy_and_iterators(_Right._Mypair._Myval2);
//     }

//     _CONSTEXPR20 _Alty& _Getal() noexcept {
//         return _Mypair._Get_first();
//     }

//     _CONSTEXPR20 const _Alty& _Getal() const noexcept {
//         return _Mypair._Get_first();
//     }

//     _Compressed_pair<_Alty, _Scary_val> _Mypair;
// };