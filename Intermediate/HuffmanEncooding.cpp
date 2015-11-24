#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

struct node {
	char ch = '\0';
	int freq = 0;
	node *right = NULL, *left = NULL;
};

struct dict {
	char key;
	string value;
};

vector<node> generateFreq(string str) {
	int index = 0;
	vector<node> tmp;
	bool flag;
	node tNode;
	for (int i = 0; i < str.size(); i++) {
		flag = false;
		for (int j = 0; j < (int)tmp.size(); j++) {
			if (tmp[j].ch == str[i]) {
				tmp[j].freq++;
				flag = true;
				break;
			}
		}
		if (flag == false) {
			tNode.ch = str[i];
			tNode.freq = 1;
			tmp.push_back(tNode);
		}
	}
	return tmp;
}

class huffmanEncode {
public:	
	node* root;

	void gotoXY(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	int whereX() {
		CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
		return consoleinfo.dwCursorPosition.X;
	}

	int whereY() {
		CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
		return consoleinfo.dwCursorPosition.Y;
	}

	int maxDepth(node *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return (left > right) ? left + 1 : right + 1;
	}

	void print(node *n, int x = 40, int y = 0, int isRight = -1) {
		int tmpY = whereY();

		if (n == NULL)  {
			gotoXY(x, y);
			cout << "Empty";
			return;
		}

		if (isRight == 1) {
			gotoXY(x + 2, y - 1);
			cout << "/";
		}

		if (isRight == 0) {
			gotoXY(x - 2, y - 1);
			cout << "\\";
		}

		gotoXY(x, y);
		if (n->ch == '\0')
			cout << n->freq << endl;
		else if (n->ch == '\n')
			cout << "NL" << endl;
		else if (n->ch == ' ')
			cout << "*" << endl;
		else
			cout << n->ch << endl;

		if (n->left != NULL) {
			print(n->left, x - 5, y + 2, 1);
		}

		if (n->right != NULL) {
			print(n->right, x + 5, y + 2, 0);
		}

		gotoXY(0, tmpY + maxDepth(&freq[0]) + 4);
	}

	vector<node> freq;
	int secLastIndex = 0, lastIndex = 0;

	void setFreq(vector<node> f) {
		freq = f;
	}

	void getTwoSmall() {
		int first = freq[0].freq, second = freq[1].freq;
		lastIndex = 0;
		secLastIndex = 1;
		for (int i = 2; i < (int)freq.size(); i++) {
			if (freq[i].freq < first) {
				second = first;
				first = freq[i].freq;
				secLastIndex = lastIndex;
				lastIndex = i;
			}
			else if (freq[i].freq < second)
			{
				second = freq[i].freq;
				secLastIndex = i;
			}
		}
		if (secLastIndex > lastIndex) {
			int tmp = lastIndex;
			lastIndex = secLastIndex;
			secLastIndex = tmp;
		}
	}

	node* getTree() {
		node tmp;
		while (freq.size() > 1) {
			getTwoSmall();
			tmp.freq = freq[secLastIndex].freq + freq[lastIndex].freq;

			node *rightNode = new node;
			*rightNode = freq[lastIndex];

			node *leftNode = new node;
			*leftNode = freq[secLastIndex];

			tmp.right = rightNode;
			tmp.left = leftNode;

			freq.erase(freq.begin() + secLastIndex);
			freq.erase(freq.begin() + lastIndex - 1);

			freq.push_back(tmp);
		}
		return &freq[0];
	}

	bool flag = false;
	string getCode(node* root, char ch) {
		string str = "";
		if (root->right == NULL && root->left == NULL) {
			if (root->ch == ch) {
				flag = true;
			}
		}
		if (root->left && flag == false) {
			str = getCode(root->left, ch);
			if (flag == true) return "0" + str;
		}
		if (root->right && flag == false) {
			str = getCode(root->right, ch);
			if (flag == true) return "1" + str;
		}
		return str;
	}

	string encode(node *root, string str, vector<node> f) {
		vector<dict> d = getDict(root, f);
		string result = "";
		for (int i = 0; i < str.size(); i++) {
			for (int j = 0; j < d.size(); j++) {
				if (d[j].key == str[i]) {
					result += d[j].value;
					break;
				}
			}
		}
		return result;
	}

	string decode(node *tmp, string str, int index = 0) {
		//cout << index;
		if (tmp->right == NULL && tmp->left == NULL) {
			return tmp->ch + decode(root, str, index);
		}
		else if (str[index] == '0')
			return decode(tmp->left, str, index + 1);
		else if (str[index] == '1')
			return decode(tmp->right, str, index + 1);
		return "";
	}

	vector<dict> getDict(node* root, vector<node> f) {
		vector<dict> d;
		for (int i = 0; i < f.size(); i++) {
			dict tmp;
			tmp.key = f[i].ch;
			flag = false;
			tmp.value = getCode(root, f[i].ch);
			d.push_back(tmp);
		}
		flag = false;
		return d;
	}
};

int main() {
	//string str = "traversing threaded binary trees\n";
	string str = "I am Syed Owais Ali Chishti";

	vector<node> freq = generateFreq(str);
	huffmanEncode h;
	h.setFreq(freq);
	h.root = h.getTree();
	string encoded = h.encode(h.root, str, freq);
	cout << encoded << endl << endl;
	string decoded = h.decode(h.root, encoded);
	cout << decoded << endl;
	return 0;
}