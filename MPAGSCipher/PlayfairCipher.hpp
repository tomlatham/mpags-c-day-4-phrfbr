#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <string>
#include <map>

// Our project headers
#include "CipherMode.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
  public:
    /**
     * Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    PlayfairCipher( const std::string key );

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;
    
    /**
     * Set the key to be used for the encryption/decryption
     *
     * \param key the key to use in the cipher
     */
    void setKey(const std::string& key);

  private:
    /// The cipher key, essentially a constant shift to be applied
    std::string key_ = "";

    /// Lookup table to go from the character to the coordinates
    std::map<char, std::pair<int,int>> l2ckeymap_;

    /// Lookup table to go from the coordinates to the character
    std::map<std::pair<int,int>, char> c2lkeymap_;
};

#endif
