//animation: https://people.ok.ubc.ca/ylucet/DS/Huffman.html
// huffman.cpp : Defines the entry point for the console application.
//
#include <queue>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
 
 
/* Interface: */
void encodeInto(string text, ostream& out);
string decodeFrom(istream& in);
 
 
/* Class prototype:
class HuffmanCode {
        public:
                string encode(string source);
                string decode(string binary);
 
                void createOptimalEncodingFromText(string text);
 
                friend ostream& operator<<(ostream& out, const HuffmanCode& object);
                friend istream& operator>>(istream& in, HuffmanCode& object);
};
*/
 
 
 
/**
 * 1
 */
 
 
class LetterGroup;
typedef LetterGroup* PLetterGroup;
 
 
/**
 * @class LetterGroup - A node in a binary Huffman tree
 * includes a group of letters, their total frequency, and pointers to the left and right sons (if not a leaf)
 */
class LetterGroup {
        private:
                string myLetters;
                int myTotalFrequency;
                PLetterGroup myLeft, myRight;
 
        public:
                LetterGroup(
                        string newLetters, int newTotalFrequency,
                        PLetterGroup newLeft=NULL, PLetterGroup newRight=NULL): 
                                myLetters(newLetters), myTotalFrequency(newTotalFrequency),
                                myLeft(newLeft), myRight(newRight) {}
 
                /* In the Huffman algorithm, the priority of the letter group is HIGHER when the frequency is LOWER! */
                bool operator== (const LetterGroup& other) { return myTotalFrequency == other.myTotalFrequency; }
                bool operator!= (const LetterGroup& other) { return myTotalFrequency != other.myTotalFrequency; }
                bool operator> (const LetterGroup& other) { return myTotalFrequency > other.myTotalFrequency; }
                bool operator< (const LetterGroup& other) { return myTotalFrequency < other.myTotalFrequency; }
                bool operator>= (const LetterGroup& other) { return myTotalFrequency >= other.myTotalFrequency; }
                bool operator<= (const LetterGroup& other) { return myTotalFrequency <= other.myTotalFrequency; }
 
                string letters() const { return myLetters; }
                int totalFrequency() const { return myTotalFrequency; }
                const PLetterGroup left() const {return myLeft;}
                const PLetterGroup right() const {return myRight;}
                
                bool isLeaf() const { return myLeft==NULL; }
                
                void destruct() {
                        if (myLeft) {
                                myLeft->destruct();
                                delete myLeft;
                        }
                        if (myRight) {
                                myRight->destruct();
                                delete myRight;
                        }
                }
 
                friend ostream& operator<<(ostream& out, const LetterGroup& object) {
                        out << object.letters() << " " << object.totalFrequency() << endl;
                        return out;
                }
}; // class LetterGroup
 
 
 
 
/**
 * 2
 */
 
class CompareLetterGroupPointer {
public:
    bool operator()(PLetterGroup a, PLetterGroup b) { 
                        return a->totalFrequency() > b->totalFrequency(); 
                }
};
 
typedef priority_queue<PLetterGroup, vector<PLetterGroup>, CompareLetterGroupPointer> LetterGroupPriorityQueue;
 
 
 
 
/**
 * 3 4
 */
 
class HuffmanCode {
        private:
                map<char,string> myEncoding;
                map<string,char> myDecoding;
        
        public:
                /// Return a binary string encoding the given text string
                string encode(string source) {
                        string binary="";
                        for (size_t i=0; i<source.length(); ++i) {
                                binary += myEncoding[source[i]];
                        }
                        return binary;
                }
                
                /// Return the original string
                string decode(string binary) {
                        string source="";
                        string currentLetterBinary="";
                        for (size_t i=0; i<binary.length(); ++i) {
                                currentLetterBinary += binary[i];
                                if (myDecoding[currentLetterBinary]) {
                                        source += myDecoding[currentLetterBinary];
                                        currentLetterBinary = "";
                                }
                        }
                        return source;
                }
 
                /// Write the entire encoding table into an output stream
                friend ostream& operator<<(ostream& out, const HuffmanCode& object) {
                        for (map<char,string>::const_iterator it=object.myEncoding.begin(); it!=object.myEncoding.end(); ++it) {
                                out << " " << it->first << it->second;
                        }
                        out << endl;
                        return out;
                }
 
                /// Read the entire encoding table from an input stream
                friend istream& operator>>(istream& in, HuffmanCode& object) {
                        char c = in.get();
                        while (c==' ') {  // read a new char encoding
                                char source = in.get();
                                string binary = "";
                                for (;;) {  // read 0's and 1's 
                                        char digit = in.get();
                                        if (digit=='0' || digit=='1') {
                                                binary += digit;
                                        } else {
                                                in.unget();
                                                break;
                                        }
                                }
                                object.myEncoding[source] = binary;
                                object.myDecoding[binary] = source;
                                c = in.get();
                        }
                        // The first char that is not '=' should be the 'endl' written at operator<<
                        return in;
                }
 
 
                /**
                 * Use a Huffman tree to create an optimal encoding to the given text
                 */
                void createOptimalEncodingFromText(string text) {
 
                        // Count the frequency of each letter in the text:
                        map<char,int> letterFrequency;
                        for (size_t i=0; i<text.length(); ++i) {
                                letterFrequency[text[i]]++;
                        }
 
                        // Create the initial priority queue:
                        LetterGroupPriorityQueue myQueue;
                        for (map<char,int>::iterator it=letterFrequency.begin(); it!=letterFrequency.end(); ++it) {
                                string singleLetter = "";
                                singleLetter += it->first;
                                PLetterGroup p = new LetterGroup(singleLetter, it->second);
                                myQueue.push(p);
                        }
                        
                        // Create the Huffman Tree:
                        while (myQueue.size()>1) {
                                PLetterGroup top1 = myQueue.top(); 
                                myQueue.pop();
                                PLetterGroup top2 = myQueue.top(); 
                                myQueue.pop();
                                PLetterGroup sum = new LetterGroup(
                                        top1->letters()+top2->letters(),
                                        top1->totalFrequency()+top2->totalFrequency(),
                                        top1, top2);
                                myQueue.push(sum);
                        }
 
                        // Create the binary Coding:
                        PLetterGroup huffmanTreeRoot = myQueue.top();
                        createEncodingFromHuffmanTreeNode("", huffmanTreeRoot);
                        huffmanTreeRoot->destruct();
                } // createOptimalEncodingFromText
 
 
 
        private:
                
                // Recursively build the binary coding from the given inner node of the Huffman Tree:
                void createEncodingFromHuffmanTreeNode(string binary, PLetterGroup theHuffmanTreeNode) {
                        if (theHuffmanTreeNode->isLeaf()) {
                                string singleLetter = theHuffmanTreeNode->letters();
                                char source = singleLetter[0];
                                myEncoding[source] = binary;
                                myDecoding[binary] = source;
                        } else {
                                createEncodingFromHuffmanTreeNode(binary+"0", theHuffmanTreeNode->left());
                                createEncodingFromHuffmanTreeNode(binary+"1", theHuffmanTreeNode->right());
                        }
                }
}; // HuffmanCode
 
 
 
 
 
/**
 * 5
 */
 
void encodeInto(string text, ostream& out) {
        HuffmanCode encoder;
        encoder.createOptimalEncodingFromText(text);
        out << encoder << encoder.encode(text);
}
 
 
string decodeFrom(istream& in) {
        HuffmanCode encoder;
        string binary;
        in >> encoder >> binary;
        return encoder.decode(binary);
}
 
 
int main()
{        // Read the entire standard input into a string:
        string text = "", line = "";
        while (getline(cin, line)) {
                text += line + "\n";
        }
 
        // Encode and decode:
        HuffmanCode theHuffmanCode;
        theHuffmanCode.createOptimalEncodingFromText(text);
        cout << "Original text:" << endl << text << endl;
        string encoded = theHuffmanCode.encode(text);
        cout << "Encoded text:" << endl << encoded << endl;
        string decoded = theHuffmanCode.decode(encoded);
        cout << "Re-decoded text:" << endl << decoded << endl;
 
        // Encode and decode all, including the encoding itself:
        ostringstream outputFile;
        encodeInto(text, outputFile);
        string outputFileContents = outputFile.str();
        cout << "Encoded text with encoding:" << endl << outputFileContents << endl;
        
        istringstream inputFile(outputFileContents);
        string decodedInputFileContents = decodeFrom(inputFile);
        cout << "Re-decoded text:" << endl << decodedInputFileContents << endl;
		system("pause");
	return 0;
}

