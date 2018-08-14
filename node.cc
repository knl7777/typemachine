// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) {
	m_data = data;
	m_prev = nullptr;
	m_next = nullptr;
	return;
}

char Node::GetData() {
  return m_data;
}

Node* Node::GetPreviousNode() {
  return m_prev;
}

Node* Node::GetNextNode() {
  return m_next;
}

Node* Node::InsertPreviousNode(char data) {
	Node* new_node = new Node(data);
	if (m_prev){
		m_prev->m_next = new_node;
	}
	new_node->m_prev = m_prev;
	new_node->m_next = this;
	m_prev = new_node;

	return new_node;
}

Node* Node::InsertNextNode(char data) {
	Node* new_node = new Node(data);
	if (m_next){
		m_next->m_prev = new_node;
	}
	new_node->m_next = m_next;

	m_next = new_node;
	new_node->m_prev = this;

	return new_node;
}

bool Node::ErasePreviousNode() {
	if (!m_prev)
		return false;

	Node* old_prev = m_prev;

	if (m_prev->m_prev){
		m_prev->m_prev->m_next = this;
	}
	m_prev = m_prev->m_prev;

	delete old_prev;

	return true;
}

bool Node::EraseNextNode() {
	if (!m_next)
		return false;

	Node *old_next = m_next;

	if (m_next->m_next){
		m_next->m_next->m_prev = this;
	}
	m_next = m_next->m_next;

	delete old_next;

	return true;
}
