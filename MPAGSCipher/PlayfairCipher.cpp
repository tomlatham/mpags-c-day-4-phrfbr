
// Standard library includes
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>

// Out project headers
#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

PlayfairCipher::PlayfairCipher( const std::string key ) : key_("")
{
	setKey(key);
}

void PlayfairCipher:: setKey(const std::string& key)
{
	// store the original key
	key_ = key;

	// Append the alphabet

	key_ += "abcdefghijklmnopqrstuvwxyz";

	// Make sure the key is upper case

	std::transform(key_.begin(), key_.end(), key_.begin(),toupper);

	// Remove non-alpha characters

	key_.erase(std::remove_if(key_.begin(),key_.end(), [] (char c) { return !std::isalpha(c); }), key_.end());

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

/*	using l2c = std::map<char, std::pair<int,int>>;
	using c2l = std::map<std::pair<int,int>, char> ;

	l2c l2ckeymap; 
	c2l c2lkeymap;
*/
	for (unsigned int i=0; i<25; ++i){

		int ix = i%5;
		int iy = i/5;

		std::pair<int, int> coord{ix, iy};
		l2ckeymap_[ key_[i] ] = coord;
		c2lkeymap_[coord] = key_[i];	
	}

	// Store the playfair cihper key map

	//Print key to check code
	std::cout << "\n" << "The keymap is: " << key_ << "\n" << std::endl;
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,  const CipherMode cipherMode ) const 
{

	std::string inputText_ { inputText };
	std::string outputText{""};
	std::string playfairText{};

	// Change J → I

	std::transform(inputText_.begin(),inputText_.end(), inputText_.begin(), [] (char j) {if (j == 'J') return 'I'; else return j;} );


	// Find repeated chars and add an X

	int n = inputText_.length();

	// Loop over the input in Digraphs

	switch (cipherMode){
		case CipherMode::Encrypt :
		{

			for (int j=0; j<n; j+=2){

				if ( j+1 == n ) {
					outputText += inputText_[j];
					break;
				}

				else if (inputText_[j] == inputText_[j+1]){
					if(inputText_[j] != 'X'){
						outputText += inputText_[j];
						outputText += 'X';
						--j;
					}
					else{
						outputText += inputText_[j];
						outputText += 'Q';
						--j;
					}
				}
				else {
					outputText += inputText_[j];
					outputText += inputText_[j+1];
				}
			}

			int m = outputText.length();
	
			if ((m) %2 != 0){
				if (outputText[m-1] == 'Z'){
					outputText += 'Q';
				}
				else{
					outputText += 'Z';
				}
			}

			std::cout << "Preciphered text is '" << outputText << "'\n" << std::endl;

			for (auto iter = std::begin(outputText); iter != outputText.end(); iter += 2){

			//   - Find the coords in the grid for each digraph
			char lett1 = *iter;
			char lett2 = *(iter + 1);

			int char1Col = (*l2ckeymap_.find(lett1)).second.first;
			int char1Row = (*l2ckeymap_.find(lett1)).second.second;

			int char2Col = (*l2ckeymap_.find(lett2)).second.first;
			int char2Row = (*l2ckeymap_.find(lett2)).second.second;


			//   - Apply the rules to these coords to get 'new' coords

			if ( char1Row == char2Row ) {
				int char1ColNew = ((char1Col + 1) %5);
				int char2ColNew = ((char2Col + 1) %5);
				lett1 = ( *c2lkeymap_.find( std::make_pair(char1ColNew, char1Row))).second;
				lett2 = ( *c2lkeymap_.find( std::make_pair(char2ColNew, char2Row))).second;
			}

			else if ( char1Col == char2Col) {
				int char1RowNew = ((char1Row + 1) %5);
				int char2RowNew = ((char2Row + 1) %5);	
				lett1 = ( *c2lkeymap_.find( std::make_pair(char1Col, char1RowNew))).second;
				lett2 = ( *c2lkeymap_.find( std::make_pair(char2Col, char2RowNew))).second;
			}

			else {
				lett1 = ( *c2lkeymap_.find( std::make_pair( char2Col,char1Row))).second;
				lett2 = ( *c2lkeymap_.find( std::make_pair( char1Col,char2Row))).second;
			}


			playfairText += lett1;
			playfairText += lett2;

			//   - Find the letter associated with the new coords

			}
			break;
		}

		case CipherMode::Decrypt :
		{
			for (auto iter = std::begin(inputText_); iter != inputText_.end(); iter += 2){

			//   - Find the coords in the grid for each digraph
			char lett1 = *iter;
			char lett2 = *(iter + 1);

			int char1Col = (*l2ckeymap_.find(lett1)).second.first;
			int char1Row = (*l2ckeymap_.find(lett1)).second.second;

			int char2Col = (*l2ckeymap_.find(lett2)).second.first;
			int char2Row = (*l2ckeymap_.find(lett2)).second.second;


			//   - Apply the rules to these coords to get 'new' coords

			if ( char1Row == char2Row ) {
				int char1ColNew = ((char1Col - 1 +5) %5);
				int char2ColNew = ((char2Col - 1 +5) %5);
				lett1 = ( *c2lkeymap_.find( std::make_pair(char1ColNew, char1Row))).second;
				lett2 = ( *c2lkeymap_.find( std::make_pair(char2ColNew, char2Row))).second;
			}

			else if ( char1Col == char2Col) {
				int char1RowNew = ((char1Row - 1 +5) %5);
				int char2RowNew = ((char2Row - 1 +5) %5);	
				lett1 = ( *c2lkeymap_.find( std::make_pair(char1Col, char1RowNew))).second;
				lett2 = ( *c2lkeymap_.find( std::make_pair(char2Col, char2RowNew))).second;
			}

			else {
				lett1 = ( *c2lkeymap_.find( std::make_pair( char2Col,char1Row))).second;
				lett2 = ( *c2lkeymap_.find( std::make_pair( char1Col,char2Row))).second;
			}


			playfairText += lett1;
			playfairText += lett2;

			//   - Find the letter associated with the new coords

			}
			break;
		}

	}
	// return the text

	std::cout << "inputText_ is '" << inputText_ << "'\n" << std::endl;
	std::cout << "Output text is '" << playfairText << "'\n" << std::endl;

return playfairText;
}
