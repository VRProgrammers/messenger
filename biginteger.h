using namespace std;

typedef struct Node {
    Node* next = NULL;
    Node* prev = NULL;
    unsigned long int data = 0;
} Node;

// class for big integer
class BigInteger {
    private:
        bool isNonNegative = true;
    public:
        Node* tail = NULL; // least significant, next is NULL
        Node* head = NULL; // most significant, prev is NULL
        int numNodes = 1;
        BigInteger() {
            this->head = new Node();
            this->tail = this->head;
        }
        BigInteger(unsigned long int integer) {
            this->head = new Node();
            this->tail = this->head;
            this->head->data = integer;
        }
        BigInteger(string strBinRepr) {
            int firstOneIndex = 0;
            this->head = new Node();
            this->tail = this->head;
            for (; strBinRepr[firstOneIndex] == 0; firstOneIndex++);
            for (int i = strBinRepr.size()-1; i >= firstOneIndex; i-=sizeof(unsigned long int)*8) {
                unsigned long int data = 0;
                unsigned long int power = 1;
                for (int j = 0; j < sizeof(unsigned long int)*8 && i-j >= 0; j++) {
                    if (strBinRepr[i-j] == '1')
                        data += power;
                    power <<= 1;
                }
                Node* newNode = new Node();
                newNode->data = data;
                newNode->next = this->head;
                this->head->prev = newNode;
                this->head = newNode;
                this->numNodes++;
            }
            this->tail = this->tail->prev;
            delete this->tail->next;
            this->numNodes--;
            this->tail->next = NULL;
        }
        string toStringBin() {
            if (this->numNodes == 1 && this->head->data == 0) {
                return "0";
            }

            string strRepr;

            bool firstTime = true;
            int idx = 0;
            Node* probe = this->head;

            for (int numNode = 0; numNode < this->numNodes; numNode++) {
                int numBit = 8 * sizeof(unsigned long int) - 1;
                if (numNode == 0) {
                    while (((probe->data >> numBit) & 1) == 0 && numBit >= 0) {
                        numBit--;
                    }
                }
                for (; numBit >=0; numBit--) {
                    if (((probe->data >> numBit) & 1) == 1) {
                        strRepr.push_back('1');
                    } else {
                        strRepr.push_back('0');
                    }
                }
                probe = probe->next;
            }
            return strRepr;
        }
        BigInteger* add(BigInteger* integer) {
            Node* probe1 = this->tail;
            Node* probe2 = integer->tail;
            BigInteger* resInteger = new BigInteger();
            unsigned long int carry = 0;
            int numBits = sizeof(unsigned long int) * 8;
            while (probe1 != NULL && probe2 != NULL) {
                unsigned long int num1 = probe1->data;
                unsigned long int num2 = probe2->data;
                unsigned long int sum = (num1 & ~(1UL << (numBits-1))) + (num2 & ~(1UL << (numBits-1))) + carry;
                carry = (sum >> (numBits-1)) + (num1 >> (numBits-1)) + (num2 >> (numBits-1));
                sum |= (carry % 2) << (numBits-1);
                sum &= ~((~carry % 2) << (numBits-1));
                carry >>= 1;
                Node* newNode = new Node();
                newNode->data = sum;
                newNode->next = resInteger->head;
                resInteger->head->prev = newNode;
                resInteger->head = newNode;
                probe1 = probe1->prev;
                probe2 = probe2->prev;
                resInteger->numNodes++;
            }
            if (probe2 != NULL)
                probe1 = probe2;

            while (probe1 != NULL) {
                Node* newNode = new Node();
                unsigned long int sum = probe1->data & ~(1UL << (numBits-1));
                sum += carry;
                carry = (sum >> (numBits-1)) + (probe1->data >> (numBits-1));
                sum |= ((carry % 2) << (numBits-1));
                sum &= ~((~carry % 2) << (numBits-1));
                newNode->data = sum;
                carry >>= 1;
                newNode->next = resInteger->head;
                resInteger->head->prev = newNode;
                resInteger->head = newNode;
                probe1 = probe1->prev;
                resInteger->numNodes++;
            }

            if (carry > 0) {
                Node* newNode = new Node();
                newNode->data = carry;
                newNode->next = resInteger->head;
                resInteger->head->prev = newNode;
                resInteger->head = newNode;
                resInteger->numNodes++;
            }
            resInteger->tail = resInteger->tail->prev;
            delete resInteger->tail->next;
            resInteger->tail->next = NULL;
            resInteger->numNodes--;
            return resInteger;
        }
};
