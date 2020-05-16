#include "pch.h"
#include "../src/string.hpp"

TEST(TrieTest, BasicTest) {
	using trie::Node;

	Node* root = new Node();

	root->insert("");
	root->insert("A");
	root->insert("AB");
	root->insert("ABBB");

	ASSERT_EQ(root->count_, 4);
	ASSERT_EQ(root->exist_, true);
	ASSERT_EQ(root->next_[0]->count_, 3);
	ASSERT_EQ(root->next_[0]->exist_, true);
	ASSERT_EQ(root->next_[0]->next_[1]->count_, 2);
	ASSERT_EQ(root->next_[0]->next_[1]->level_, 2);
	ASSERT_EQ(root->next_[0]->next_[1]->exist_, true);
	ASSERT_EQ(root->next_[0]->next_[1]->next_[1]->exist_, false);
}
