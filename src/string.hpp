#include <string>
#include <cstring>

namespace trie {
    using std::string;
    const int N_CHARSET = 26;
    struct Node {
        bool exist_;
        int count_;
        int level_;
        Node* next_[N_CHARSET];
        char base_;

        Node(char base = 'A', int level = 0, bool is_string = false, int count = 0) : exist_(is_string), count_(count), base_(base), level_(level) {
            for (int i = 0; i < N_CHARSET; i++) {
                this->next_[i] = nullptr;
            }
        }

        void insert(const string& s, int i) {
            this->count_++;
            if (i == s.size()) {
                this->exist_ = true;
                return;
            }
            int offset = s[i] - this->base_;
            Node* that = this->next_[offset];
            if (that == nullptr) {
                this->next_[offset] = new Node(this->base_, this->level_ + 1);
                that = this->next_[offset];
            }

            that->insert(s, i + 1);
        }

        void insert(const string& s) {
            this->insert(s, 0);
        }
    };
}
