#ifndef KGL_BASE_BITSET_H_INCLUDED
#define KGL_BASE_BITSET_H_INCLUDED

#include <cassert>
#include <vector>

namespace KGL {

namespace XBitset
{

class BitsetBase
{
public:
    BitsetBase() :
        m_size(0), m_mem(nullptr)
    {
    }

    explicit BitsetBase(uint8_t* mem, int bitsetSize) :
        m_size(bitsetSize), m_mem(mem)
    {
    }

    BitsetBase(const BitsetBase&) = default;

    int Size() const { return m_size; }

    bool IsSet(int idx) const
    {
        assert(idx < m_size);

        return (m_mem[idx >> 3] & static_cast<uint8_t>(1 << (idx & 0x7))) != 0;
    }

    bool All() const
    {
        const int bytes = m_size >> 3;

        for(int i = 0; i < bytes; ++i)
        {
            if(m_mem[i] != 0xff)
            {
                return false;
            }
        }

        const int div = m_size & 0x7;

        if(div > 0)
        {
            const uint8_t byte = m_mem[bytes];

            for(int i = 0; i < div; ++i)
            {
                if((byte & static_cast<uint8_t>(1 << i)) == 0)
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool Any() const
    {
        const int bytes = m_size >> 3;

        for(int i = 0; i < bytes; ++i)
        {
            if(m_mem[i])
            {
                return true;
            }
        }

        const int div = m_size & 0x7;

        if(div > 0)
        {
            const uint8_t byte = m_mem[bytes];

            for(int i = 0; i < div; ++i)
            {
                if((byte & static_cast<uint8_t>(1 << i)) != 0)
                {
                    return true;
                }
            }
        }

        return false;
    }

    int Count() const
    {
        const int bytes = m_size >> 3;
        int count = 0;

        for(int i = 0; i < bytes; ++i)
        {
            count += bitsInByte[m_mem[i]];
        }

        const int div = m_size & 0x7;

        if(div > 0)
        {
            const uint8_t byte = m_mem[bytes];

            for(int i = 0; i < div; ++i)
            {
                if((byte & static_cast<uint8_t>(1 << i)) != 0)
                {
                    ++count;
                }
            }
        }

        return count;
    }

    void Set(int idx, bool val = true)
    {
        assert(idx < m_size);

        if(val)
        {
            m_mem[idx >> 3] |= static_cast<uint8_t>(1 << (idx & 0x7));
        }
        else
        {
            m_mem[idx >> 3] &= ~static_cast<uint8_t>(1 << (idx & 0x7));
        }
    }

    bool SetUnique(int idx, bool val = true)
    {
        assert(idx < m_size);

        const uint8_t mask = static_cast<uint8_t>(1 << (idx & 0x7));

        if(val)
        {
            if((m_mem[idx >> 3] & mask) == 0)
            {
                m_mem[idx >> 3] |= mask;

                return true;
            }
        }
        else
        {
            if((m_mem[idx >> 3] & mask) != 0)
            {
                m_mem[idx >> 3] &= ~mask;

                return true;
            }
        }

        return false;
    }

    void GetIndices(bool bit, std::vector<int>* indices) const
    {
        const int bytes = m_size >> 3;
        const int div = m_size & 0x7;

        if(bit)
        {
            for(int i = 0, j = 0; i < bytes; ++i, j += 8)
            {
                if(m_mem[i] != 0)
                {
                    const int8_t* x = setBitIndicesInByte[m_mem[i]];

                    indices->push_back(j + *x++);

                    for(int k = 1; k < 8 && *x >= 0; ++k, ++x)
                    {
                        indices->push_back(j + *x);
                    }
                }
            }

            if(div > 0)
            {
                const uint8_t byte = m_mem[bytes];

                for(int i = 0; i < div; ++i)
                {
                    if((byte & static_cast<uint8_t>(1 << i)) != 0)
                    {
                        indices->push_back((bytes << 3) + i);
                    }
                }
            }
        }
        else
        {
            for(int i = 0, j = 0; i < bytes; ++i, j += 8)
            {
                if(m_mem[i] != 0xff)
                {
                    const int8_t* x = unsetBitIndicesInByte[m_mem[i]];

                    indices->push_back(j + *x++);

                    for(int k = 1; k < 8 && *x >= 0; ++k, ++x)
                    {
                        indices->push_back(j + *x);
                    }
                }
            }

            if(div > 0)
            {
                const uint8_t byte = m_mem[bytes];

                for(int i = 0; i < div; ++i)
                {
                    if((byte & static_cast<uint8_t>(1 << i)) == 0)
                    {
                        indices->push_back((bytes << 3) + i);
                    }
                }
            }
        }
    }

    void Reset(bool val = false);

    BitsetBase& operator=(const BitsetBase&) = default;

protected:
    // size in bits
    int m_size;
    // chunk of memory at least sizeof m_size / 8 + 1
    uint8_t* m_mem;

private:
    static const uint8_t bitsInByte[256];
    static const int8_t setBitIndicesInByte[256][8];
    static const int8_t unsetBitIndicesInByte[256][8];
};

}

class BitsetInMem : public XBitset::BitsetBase
{
public:
    BitsetInMem()
    {
    }

    explicit BitsetInMem(uint8_t* mem, int bitsetSize) :
        BitsetBase(mem, bitsetSize)
    {
    }

    explicit BitsetInMem(uint8_t* mem, int bitsetSize, bool init) :
        BitsetBase(mem, bitsetSize)
    {
        Reset(init);
    }

    BitsetInMem(const BitsetInMem&) = default;

    uint8_t* Memory() const { return m_mem; }

    BitsetInMem& operator=(const BitsetInMem&) = default;
};

class Bitset : public XBitset::BitsetBase
{
public:
    Bitset()
    {
    }

    explicit Bitset(int bitsetSize, bool init) :
        m_blob((bitsetSize >> 3) + ((bitsetSize & 0x7) ? 1 : 0), init ? 0xff : 0)
    {
        m_size = bitsetSize;
        m_mem = m_blob.data();
    }

    Bitset(const Bitset&) = delete;

    ~Bitset()
    {
    }

    void Resize(int bitsetSize, bool init)
    {
        m_blob.resize((bitsetSize >> 3) + ((bitsetSize & 0x7) ? 1 : 0), init ? 0xff : 0);

        m_size = bitsetSize;
        m_mem = m_blob.data();
    }

    void Clear()
    {
        m_blob.clear();

        m_size = 0;
        m_mem = nullptr;
    }

    Bitset& operator=(const Bitset&) = delete;

private:
    std::vector<uint8_t> m_blob;
};

}

#endif /*KGL_BASE_BITSET_H_INCLUDED*/