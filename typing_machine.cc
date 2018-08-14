// Copyright 2018 <Author>

#include "typing_machine.h"

void TypingMachine::RemoveSelf(Node* node){
	if (!node)
		return;

	if (node->GetPreviousNode())
		node->GetPreviousNode()->EraseNextNode();
	else if (node->GetNextNode())
		node->GetNextNode()->ErasePreviousNode();
}

TypingMachine::TypingMachine() {
	m_cursor = new Node(0);
	m_head = m_cursor;
	m_length = 0;
}

void TypingMachine::HomeKey() {
	if (!m_cursor || m_cursor == m_head)
		return;

	m_head = m_head->InsertPreviousNode(0);
	RemoveSelf(m_cursor);
	m_cursor = m_head;
		
	return;
}

void TypingMachine::EndKey() {
	if (!m_cursor)
		return;

	Node* t = m_head;
	Node* new_cursor;
	while (t->GetNextNode()){
		t = t->GetNextNode();
	}
	
	if (m_cursor == t)
		return;

	new_cursor = t->InsertNextNode(0);
	if (m_cursor == m_head)
		m_head = m_head->GetNextNode();
	RemoveSelf(m_cursor);
	m_cursor = new_cursor;
	return;
}

void TypingMachine::LeftKey() {
	Node* old_cursor = m_cursor;
	Node* t = m_cursor->GetPreviousNode();
	if (t){
		m_cursor = m_cursor->GetPreviousNode()->InsertPreviousNode(0);
		RemoveSelf(old_cursor);
		if (t == m_head)
			m_head = m_cursor;
	}
	return;
}

void TypingMachine::RightKey() {
	Node* old_cursor = m_cursor;
	Node* t = m_cursor->GetNextNode();

	if (t){
		m_cursor = m_cursor->GetNextNode()->InsertNextNode(0);
		RemoveSelf(old_cursor);
		if (old_cursor == m_head)
			m_head = t;
	}
	return;
}

bool TypingMachine::TypeKey(char key) {
	if (key < 32 && key > 126)
		return false;

	if (m_length >= 100)
		return false;

	Node* t = m_cursor->InsertPreviousNode(key);
	if (m_head == m_cursor)
		m_head = t;

	m_length++;
	return true;
}

bool TypingMachine::EraseKey() {
	if (!m_head || !m_cursor)
		return false;

	Node* t = m_cursor->GetPreviousNode();
	if (t){
		m_cursor->ErasePreviousNode();
		if (t == m_head)
			m_head = m_cursor;
		m_length--;
		return true;
	}

	return false;
}

std::string TypingMachine::Print(char separator) {
	Node* t = m_head;
	std::string str;

	while (t){
		if (t == m_cursor){
			if (separator != 0){
				str.push_back(separator);
			}
		}
		else{
			str.push_back(t->GetData());
		}
		
		t = t->GetNextNode();
	}

	return str;
}
