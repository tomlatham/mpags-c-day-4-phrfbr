
// Standard library includes
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

// Out project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string key ) : key_("")
  
{
    setKey(key);
}

void PlayfairCipher:: setKey(const std::string& key){
	// store the original key
	key_ = key;
	// Append the alphabet

	key_ += "abcdefghijklmnopqrstuvwxyz";

	// Make sure the key is upper case

	std::transform(key_.begin(), key_.end(), key_.begin(),toupper);

	// Remove non-alpha characters

	key_.erase(std::remove_if(key_.begin(),key_.end(), [] (unsigned char c) { return !std::isalpha(c); }), key_.end());

	// Change J -> I

	std::transform(key_.begin(),key_.end(), key_.begin(), [] (char j) {if (j == 'J') return 'I'; else return j;} );

	// Remove duplicated letters

	std::string LtrSeen{""}; 

	auto func = [&] (char b) {
		if ( LtrSeen.find(b) != std::string::npos ){
			return true;
		}
		else {
			LtrSeen += b;
			return false;
		}
	}; 

	key_.erase(std::remove_if(key_.begin(),key_.end(),func), key_.end());

	// Store the coords of each letter

	using l2c = std::map<char, std::pair<int,int>>;
	using c2l = std::map<std::pair<int,int>, char> ;

	l2c l2ckeymap; 
	c2l c2lkeymap;

	for (unsigned int i=0; i<25; ++i){

		int ix = i%5;
		int iy = i/5;

		std::pair<int, int> coord{ix, iy};
		l2ckeymap[ key_[i] ] = coord;
		c2lkeymap[coord] = key_[i];	
	}

	// Store the playfair cihper key map

//Print key to check code
std::cout << key_ << std::endl;


}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode /*cipherMode*/ ) const 
{


	// Change J → I
	// Find repeated chars and add an X
	// if the size of input is odd, add a trailing Z
	// Loop over the input in Digraphs
	//   - Find the coords in the grid for each digraph
	//   - Apply the rules to these coords to get 'new' coords
	//   - Find the letter associated with the new coords
	// return the text
	std::cout << "CONGRATULATIONS YOU'RE NOT AN IDIOT" << std::endl;

return inputText;
}
