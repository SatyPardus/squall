#ifndef STORM_HASH_HASHKEY_HPP
#define STORM_HASH_HASHKEY_HPP

#include <cstdint>

class HASHKEY_NONE {
    public:
    // Member functions
    bool operator==(const HASHKEY_NONE& key);
};

class HASHKEY_PTR {
    public:
    // Member functions
    HASHKEY_PTR();
    HASHKEY_PTR(void* key);
    HASHKEY_PTR& operator=(const HASHKEY_PTR& key);
    bool operator==(const HASHKEY_PTR& key) const;
    void* GetPtr() const;

    private:
    // Member variables
    void* m_key;
};

class HASHKEY_INT {
    public:
    // Member functions
    HASHKEY_INT();
    HASHKEY_INT(int32_t key);
    HASHKEY_INT& operator=(const HASHKEY_INT& key);
    bool operator==(const HASHKEY_INT& key) const;
    int32_t GetValue() const;

    private:
    // Member variables
    int32_t m_key;
};

class HASHKEY_STR {
    public:
    // Member functions
    HASHKEY_STR();
    HASHKEY_STR(const char* str);
    ~HASHKEY_STR();
    HASHKEY_STR& operator=(const char* str);
    HASHKEY_STR& operator=(const HASHKEY_STR& key);
    bool operator==(const char* str) const;
    bool operator==(const HASHKEY_STR& key) const;
    const char* GetString() const;

    protected:
    // Member variables
    char* m_str;
};

class HASHKEY_STRI : public HASHKEY_STR {
    public:
    // Member functions
    HASHKEY_STRI() : HASHKEY_STR() {};
    HASHKEY_STRI(const char* str) : HASHKEY_STR(str) {};
    HASHKEY_STRI& operator=(const char* str);
    HASHKEY_STRI& operator=(const HASHKEY_STRI& key);
    bool operator==(const char* str) const;
    bool operator==(const HASHKEY_STRI& key) const;
};

class HASHKEY_CONSTSTR {
    public:
    // Member functions
    HASHKEY_CONSTSTR();
    HASHKEY_CONSTSTR(const char* str);
    ~HASHKEY_CONSTSTR();
    HASHKEY_CONSTSTR& operator=(const char* str);
    HASHKEY_CONSTSTR& operator=(const HASHKEY_CONSTSTR& key);
    bool operator==(const char* str) const;
    bool operator==(const HASHKEY_CONSTSTR& key) const;
    const char* GetString() const;

    protected:
    // Member variables
    const char* m_str;
};

class HASHKEY_CONSTSTRI : public HASHKEY_CONSTSTR {
    public:
    // Member functions
    HASHKEY_CONSTSTRI() : HASHKEY_CONSTSTR() {};
    HASHKEY_CONSTSTRI(const char* str) : HASHKEY_CONSTSTR(str) {};
    HASHKEY_CONSTSTRI& operator=(const char* str);
    HASHKEY_CONSTSTRI& operator=(const HASHKEY_CONSTSTRI& key);
    bool operator==(const char* str) const;
    bool operator==(const HASHKEY_CONSTSTRI& key) const;
};

#endif
