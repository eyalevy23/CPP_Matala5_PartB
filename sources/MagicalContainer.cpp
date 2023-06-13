#include "MagicalContainer.hpp"

namespace ariel {

    bool isPrime(int num)
    {
        if (num <= 1)
        {
            return false;
        }
        for (int i = 2; i <= sqrt(num); i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    void MagicalContainer::addElement(int element) 
    {
        _containerEle.push_back(element);
        update_ascendingVec();
        update_sideCrossVec();
        update_primeVec();
    }

    void MagicalContainer::removeElement(int element) 
    {
        auto it = std::find(_containerEle.begin(), _containerEle.end(), element);
        if(it == _containerEle.end())
        {
            throw std::runtime_error("The element is not in the container");
        }

        if (it != _containerEle.end())
        {
            _containerEle.erase(it);
        }
        update_ascendingVec();
        update_sideCrossVec();
        update_primeVec();
        
    }

    int MagicalContainer::size() const 
    {
        return _containerEle.size();
    }


    void MagicalContainer::update_ascendingVec() 
    {
        _ascendingVec.clear();
        for (decltype(_containerEle.size()) i = 0; i < _containerEle.size(); i++)
        {
            _ascendingVec.push_back(&_containerEle[i]);
        }

        std::sort(_ascendingVec.begin(), _ascendingVec.end(), [](const int* a, const int* b) 
        {
            return *a < *b;
        });
    }

        
    void MagicalContainer::update_sideCrossVec()
    {
        _sideCrossVec.clear();

        if (!_containerEle.empty())
        {
            auto start = _containerEle.begin();
            auto end = _containerEle.end() - 1;

            while (start <= end)
            {
                _sideCrossVec.push_back(&(*start));
                if (start != end)
                    _sideCrossVec.push_back(&(*end));

                ++start;
                --end;
            }
        }
    }

    void MagicalContainer::update_primeVec()
    {
        _primeVec.clear();
        for (auto it = _containerEle.begin(); it != _containerEle.end(); ++it)
        {
            if (isPrime(*it))
            {
                _primeVec.push_back(&(*it));
            }
        }
    }


    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) 
        : container(container), iter(container._ascendingVec.begin()), position(0)
    {
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) 
        : container(other.container), iter(other.iter), position(other.position)
    {
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) 
    { 
        if(&container == &other.container)
        {
            iter = other.iter;
            position = other.position;
            container = other.container;
            return *this;
        }
        throw std::runtime_error("The iterators are not from the same container");  
    };


    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin()
    {
       iter = container._ascendingVec.begin();
         position = 0;
        return *this;
    }
    
       MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end()
    {
        iter = container._ascendingVec.end();
        position = container._ascendingVec.size();
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if(iter == container._ascendingVec.end())
        {
            throw std::runtime_error("The iterator is already at the end of the container");
        }
        ++iter;
        ++position;
        return *this;   
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter == other.iter;
        }
        throw std::runtime_error("The iterators are not from the same container");
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter > other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter < other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    int MagicalContainer::AscendingIterator::operator*()
    {
        if(iter == container._ascendingVec.end())
        {
            throw std::runtime_error("The iterator is already at the end of the container");
        }
        return **iter;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) 
        : container(container), iter(container._sideCrossVec.begin()), position(0)
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) 
        : container(other.container), iter(other.iter), position(other.position)
    {
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin()
    {
        iter = container._sideCrossVec.begin();
        position = 0;
        return *this;
    }
    
       MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end()
    {
        iter = container._sideCrossVec.end();
        position = container._sideCrossVec.size();
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if(iter == container._sideCrossVec.end())
        {
            throw std::runtime_error("The iterator is already at the end of the container");
        }
        ++iter;
        ++position;
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter == other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter > other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter < other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    int MagicalContainer::SideCrossIterator::operator*()
    {
        if(iter == container._sideCrossVec.end())
        {
            throw std::runtime_error("The iterator is already at the end of the container");
        }
        return **iter;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) 
        : container(container), iter(container._primeVec.begin()), position(0)
    {
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) 
        : container(other.container), iter(other.iter), position(other.position)
    {
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin()
    {
        iter = container._primeVec.begin();
        position = 0;
        return *this;
    }
    
       MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end()
    {
        iter = container._primeVec.end();
        position = container._primeVec.size();
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if(iter == container._primeVec.end())
        {
            throw std::runtime_error("The iterator is already at the end of the container");
        }
        ++iter;
        ++position;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter == other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter > other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        if(&container == &other.container)
        {
            return iter < other.iter;
        }
        throw std::invalid_argument("The iterators are not from the same container");
    }

    int MagicalContainer::PrimeIterator::operator*()
    {
        if(iter == container._primeVec.end())
        {
            throw std::runtime_error("The iterator is already at the end of the container");
        }
        return **iter;
    }

}