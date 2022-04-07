namespace dvfw {
namespace gen {
template <typename T, int Num = -1, bool Infinite = (Num < 0)>
class value : public base_generator<T> {
   private:
    T _value;
    std::size_t _numVals;
    std::size_t _sent{0};

   public:
    value() = default;
    value(T value) : _value{value} {};

    bool hasNext() { return _sent < Num; }

    T next() {
        if (!Infinite){
            _sent++;
        }
        return _value;
    }
};
}  // namespace gen
}  // namespace dvfw
