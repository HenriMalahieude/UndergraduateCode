//Created by Henri Malahieude and Polished by Padma Bellamkonda
#include <iostream>
#include <vector>

using namespace std;
const vector<int> primes = { //Pre-generated using "Sieve of Eratosthenes" (total of 303 primes)
	2,3,5,7,11,13,17,19,23,29,31,
	37,41,43,47,53,59,61,67,71,73,
	79,83,89,97,101,103,107,109,113,127,
	131,137,139,149,151,157,163,167,173,179,
	181,191,193,197,199,211,223,227,229,233,
	239,241,251,257,263,269,271,277,281,283,
	293,307,311,313,317,331,337,347,349,353,
	359,367,373,379,383,389,397,401,409,419,
	421,431,433,439,443,449,457,461,463,467,
	479,487,491,499,503,509,521,523,541,547,
	557,563,569,571,577,587,593,599,601,607,
	613,617,619,631,641,643,647,653,659,661,
	673,677,683,691,701,709,719,727,733,739,
	743,751,757,761,769,773,787,797,809,811,
	821,823,827,829,839,853,857,859,863,877,
	881,883,887,907,911,919,929,937,941,947,
	953,967,971,977,983,991,997,1009,1013,1019,
	1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,
	1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,
	1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,
	1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,
	1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,
	1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,
	1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,
	1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,
	1601,1607,1609,1613,1619,1621,1627,1637,1657,1663,
	1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,
	1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,  
	1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,
	1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,
	1997,1999,
};

const vector<string> encoding = {
	"A", "B", "C", "D", "E", "F", "G", "H", 
	"I", "J", "K", "L", "M", "N", "O", "P", 
	"Q", "R", "S", "T", "U", "V", "W", "X", 
	"Y", "Z", " ", "\"", ",", ".", "'"
};

//Standard Trial Division, not most efficient but works. Could replace with binary search since we have 100+ ordered primes
bool isPrime(int a){
	for (int i = 0; i*i <= a; i++){
		if (a % primes.at(i) == 0) return false;
	}

	return true;
}

//To avoid overflow
int modBySquares(unsigned long long int base, int exponent, int mod){
	unsigned long long int outside = 1;
	
	while (exponent > 1){ //bad practice to use parameters like variable, but I'm not in the mood rn
		if (exponent % 2 != 0){
			outside *= base; outside %= mod;
			exponent -= 1; 
			continue;
		}

		base *= base; base %= mod;
		exponent /= 2;
	}

	return (base * outside) % mod;
}

int main(){
	int encryptionKey = 0;
	cin >> encryptionKey;

	long long int n = 0;
	cin >> n;

	int messAm = 0;
	cin >> messAm;

	vector<unsigned long long int> message(messAm);
	for (int i = 0; i < messAm; i++){
		cin >> message.at(i);
	}

	if (n < 0 || encryptionKey < 0 || messAm < 0){
		cout << "Public key is not valid!" << endl;
		return 0;
	}

	//Determine P and Q
	unsigned long long int p = 0, q = 0;
	for (int i = 0; i < primes.size(); i++){
		if (n % primes.at(i) == 0){ //check that this division is clean
			int potentialQ = n / primes.at(i);
			if (primes.at(i) != potentialQ && isPrime(potentialQ)){ //Ok we have prime #1 and potential next prime
				p = primes.at(i);
				q = potentialQ;
				break;
			}
		}

		if (primes.at(i) > n){ //potential optimization point
			break; //Means we couldn't find a solid solution for it.
		}
	}

	if (p == 0 || q == 0){ 
		cout << "Public key is not valid!" << endl;
		return 0;
	}

	//D = e^(-1) mod(phi(n))
	int decryptionKey = 0;
	unsigned long long int phi = (p-1)*(q-1); //totient
	for (int i = 1; i < phi; i++){ //no Idea how to actually find D efficiently
		int de = encryptionKey*i;
		if (de % phi == 1){
			decryptionKey = i;
			break;
		}
	}

	if (decryptionKey == 0){
		cout << "Public key is not valid!" << endl;
		return 0;
	}

	//Output Correctly
	cout << p << " " << q << " " << phi << " " << decryptionKey << endl;

	for (int i = 0; i < message.size(); i++){
		message.at(i) = modBySquares(message.at(i), decryptionKey, n); // c^d mod n
		cout << message.at(i) << " ";
	}
	cout << endl;

	for (int i = 0; i < message.size(); i++){
		int end = message.at(i) - 5;
		if (end < encoding.size()){
			cout << encoding[end];
		}
	}

	return 0;
}