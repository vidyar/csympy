#include "symbol.h"
#include "integer.h"

namespace CSymPy {

Symbol::Symbol(const std::string &name)
    : name_{name}
{
}

std::size_t Symbol::__hash__() const
{
    std::hash<std::string> hash_fn;
    return hash_fn(name_);
}

bool Symbol::__eq__(const Basic &o) const
{
    if (is_a<Symbol>(o))
        return name_ == static_cast<const Symbol &>(o).name_;
    return false;
}

int Symbol::compare(const Basic &o) const
{
    CSYMPY_ASSERT(is_a<Symbol>(o))
    const Symbol &s = static_cast<const Symbol &>(o);
    if (name_ == s.name_) return 0;
    return name_ < s.name_ ? -1 : 1;
}

std::string Symbol::__str__() const
{
    return name_;
}

RCP<const Basic> Symbol::diff(const RCP<const Symbol> &x) const
{
    if (x->name_ == this->name_)
        return one;
    else
        return zero;
}

// Initialize the special symbols.
RCP<const Symbol> pi = rcp(new Symbol("pi"));
RCP<const Symbol> E = rcp(new Symbol("E"));

} // CSymPy
