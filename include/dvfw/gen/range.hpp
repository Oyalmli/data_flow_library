namespace dvfw {
namespace gen {
template <typename T>
class range : public base_generator<T> {
   private:
    T _min, _max, _step, _curr;

   public:
    range() = default;
    range(T max) : _min{0}, _max{max}, _step{1}, _curr{0} {};
    range(T min, T max) : _min{min}, _max{max}, _step{1}, _curr{min} {};
    range(T min, T max, T step) : _min{min}, _max{max}, _step{step}, _curr{min} {};

    bool hasNext() {
        return _max > _curr;
    }

    T next() {
        T temp = _curr;
        _curr += _step;
        return temp;
    }
};
}  // namespace gen
}  // namespace dvfw
