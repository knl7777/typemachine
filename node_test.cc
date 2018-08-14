// Copyright 2018 Minkyu Jo

#include "node.h"
#include "node_test.h"
#include "test.h"

class NodeConstructorTestSuite
{
private:
  static void SingleNodeTest() {
    Node *node = new Node('A');
    ASSERT_EQ(node->GetData(), 'A');
    delete node;
  }

public:
  static void RunTest() {
    SingleNodeTest();
  }
};

class NodeInsertTestSuite
{
private:
	static void AddFrontTest(){
		Node* node = new Node('b');
		Node* new_node = node->InsertPreviousNode('a');
		ASSERT_NE(new_node, nullptr);
		ASSERT_EQ(node->GetPreviousNode(), new_node);
		ASSERT_EQ(new_node->GetData(), 'a');
		DeleteList(node);
	}
	static void AddLastTest(){
		Node* node = new Node('a');
		Node* new_node = node->InsertNextNode('b');
		ASSERT_NE(new_node, nullptr);
		ASSERT_EQ(node->GetNextNode(), new_node);
		ASSERT_EQ(new_node->GetPreviousNode(), node);
		ASSERT_EQ(new_node->GetData(), 'b');
		DeleteList(node);
	}
	static void AddMiddleTest(){
		Node* node = new Node('a');
		Node* new_node = node->InsertNextNode('c');
		new_node = new_node->InsertPreviousNode('b');
		ASSERT_EQ(node->GetNextNode(), new_node);
		DeleteList(node);

		node = new Node('a');
		new_node = node->InsertNextNode('c');
		new_node = node->InsertNextNode('b');
		ASSERT_EQ(new_node->GetNextNode()->GetData(), 'c');
		ASSERT_EQ(new_node->GetPreviousNode()->GetData(), 'a');
		DeleteList(node);
	}

	static void AddMaxNodesTest(){
		Node* node = new Node('a');
		Node* head = node;
		for (int i = 0; i < 99; i++){
			node = node->InsertNextNode('a' + i);
		}
		
		for (int i = 0; i < 99; i++){
			node = node->GetPreviousNode();
		}

		ASSERT_EQ(node, head);
	}
	static void EdgeTest(){
		Node* node = new Node('a');
		ASSERT_FALSE(node->GetNextNode());
		ASSERT_FALSE(node->GetPreviousNode());
		ASSERT_FALSE(node->ErasePreviousNode());
		ASSERT_FALSE(node->EraseNextNode());
		DeleteList(node);
	}
	static void RemoveTest(){
		Node* node = new Node('a');
		node = node->InsertNextNode('b');
		node->InsertNextNode('c');
		node->ErasePreviousNode();
		ASSERT_FALSE(node->GetPreviousNode());
		node->EraseNextNode();
		ASSERT_FALSE(node->GetNextNode());
		DeleteList(node);

		Node * head;
		head = node = new Node('a');
		node = node->InsertNextNode('b');
		node = node->InsertNextNode('c');
		node = node->InsertNextNode('d');
		node->ErasePreviousNode();
		ASSERT_EQ(node->GetPreviousNode()->GetData(), 'b');
		head->EraseNextNode();
		ASSERT_EQ(head->GetNextNode()->GetData(), 'd');
		DeleteList(head);
	}

	/* remove list */
	static void DeleteList(Node* node){
		if (!node)
			return;

		/* move to head */
		while (node->GetPreviousNode()){
			node = node->GetPreviousNode();
		}

		/* delete nodes */
		while (node){
			Node* next = node->GetNextNode();
			delete node;
			node = next;
		}
	}

public:
  static void RunTest() {
	  AddFrontTest();
	  AddLastTest();
	  AddMiddleTest();
	  AddMaxNodesTest();
	  EdgeTest();
	  RemoveTest();
  }
};

void NodeTest() {
  NodeConstructorTestSuite::RunTest();
  NodeInsertTestSuite::RunTest();
}