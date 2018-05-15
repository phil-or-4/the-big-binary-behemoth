/*
Author: Phillip Sopt
Description:
This is the set of test cases I made for the bst.h. It should cover all the cases for every function.
Note that these set of test cases were written using Visual Studios testing framework. So if you want to use them,
either convert them to regular old assert commands in C++ or import it into Visual Studio.

*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "bst.h"
#include<string>
#include<atltrace.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int cmpVectors(vector<int> expected, vector<int> actual) {
			wchar_t msg[200];
			if (expected.size() != actual.size()) {
				ATLTRACE2(L"Actual size doesn't equal expected. Got %d when expected %d\n", actual.size(), expected.size());
				//Assert::Fail();
				return 0;
			}
			int size = actual.size();
			for (int i = 0; i < size; i++)
			{
				if (expected.at(i) != actual.at(i)) {
					ATLTRACE2(msg, L"vectors not equal at i=%d, expected:%d got:%d\n", i, expected.at(i), actual.at(i));
					Assert::Fail();
					return i; //return the place were it failed
				}
			}
			return -1; //everything passed
		}

		bool isNull(vector<int>* thing) {
			if (thing == nullptr)return true;
			return false;
		}

		TEST_METHOD(testToVector)
		{
			bst<int> *tree = new bst<int>();
			Assert::AreEqual(true, isNull(tree->to_vector()), L"vector not null");
			vector<int> temp = { 1,2,3,4,5,6,7,8,9,10 };
			tree = tree->from_sorted_vec(temp, 1);
			vector<int> *temp1 = tree->to_vector();
			cmpVectors(temp, *temp1);
			tree = tree->from_sorted_vec(temp, 10);
			temp1 = tree->to_vector();
			cmpVectors(temp, *temp1);

		}

		TEST_METHOD(testCountBookkeeping) {
			bst<int> tree = bst<int>();
			int x = 2;
			tree.insert(x);
			Assert::AreEqual(1, tree.findNode(2)->count, L"count not 1", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(2)->lcount, L"count not 1", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(2)->rcount, L"count not 1", LINE_INFO());
			x = 1;
			tree.insert(x);
			Assert::AreEqual(2, tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(2)->lcount, L"lcount for node 2", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(2)->rcount, L"rcount for node2 ", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(1)->count, L"count for node 1", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(1)->lcount, L"lcount for node 1", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(1)->rcount, L"rcount for node 1", LINE_INFO());
			x = 3;
			tree.insert(x);
			Assert::AreEqual(3, tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(2)->lcount, L"lcount for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(2)->rcount, L"rcount for node2 ", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(1)->count, L"count for node 1", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(1)->lcount, L"lcount for node 1", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(1)->rcount, L"rcount for node 1", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(3)->count, L"count for node 3", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(3)->lcount, L"lcount for node 3", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(3)->rcount, L"rcount for node 3", LINE_INFO());
			x = 4;
			tree.insert(x);
			Assert::AreEqual(4, tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(1)->count, L"count for node 1", LINE_INFO());
			Assert::AreEqual(2, tree.findNode(3)->count, L"count for node 3", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(4)->count, L"count for node 4", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(1)), tree.findNode(1)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(3)), tree.findNode(3)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(4)), tree.findNode(4)->count, L"count for node 2", LINE_INFO());
			tree.remove(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(1)), tree.findNode(1)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(3)), tree.findNode(3)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(3)->rcount, L"count for node 2", LINE_INFO());
			Assert::AreEqual(0, tree.findNode(3)->lcount, L"count for node 2", LINE_INFO());
			tree.insert(x);
			x = 5;
			tree.insert(x);
			x = 3;
			tree.remove(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(1)), tree.findNode(1)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(4)), tree.findNode(4)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(4, tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(2, tree.findNode(2)->rcount, L"count for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(2)->lcount, L"count for node 2", LINE_INFO());
			x = 4;
			tree.remove(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(1)), tree.findNode(1)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(3, tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(2)->rcount, L"count for node 2", LINE_INFO());
			Assert::AreEqual(1, tree.findNode(2)->lcount, L"count for node 2", LINE_INFO());
			x = 6;
			tree.insert(x);
			x = 7;
			tree.insert(x);
			x = 8;
			tree.insert(x);
			x = 9;
			tree.insert(x);
			x = 10;
			tree.insert(x);
			x = 11;
			tree.insert(x);
			x = 12;
			tree.insert(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			x = 8;
			tree.remove(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node i", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)->left), tree.findNode(2)->lcount, L"lcount for node i", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)->right), tree.findNode(2)->rcount, L"rcount for node i", LINE_INFO());
			x = 6;
			tree.remove(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node i", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)->left), tree.findNode(2)->lcount, L"lcount for node i", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)->right), tree.findNode(2)->rcount, L"rcount for node i", LINE_INFO());
			x = 11;
			tree.remove(x);
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node 2", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)), tree.findNode(2)->count, L"count for node i", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)->left), tree.findNode(2)->lcount, L"lcount for node i", LINE_INFO());
			Assert::AreEqual(tree.countSubtree(tree.findNode(2)->right), tree.findNode(2)->rcount, L"rcount for node i", LINE_INFO());

			tree.~bst();
			tree = bst<int>();


			for (int i = 0; i < 100; i++)
			{
				tree.insert(i);
				Assert::AreEqual(tree.countSubtree(tree.findNode(i)), tree.findNode(i)->count, L"count for node i", LINE_INFO());
				Assert::AreEqual(tree.countSubtree(tree.findNode(i)->left), tree.findNode(i)->lcount, L"lcount for node i", LINE_INFO());
				Assert::AreEqual(tree.countSubtree(tree.findNode(i)->right), tree.findNode(i)->rcount, L"rcount for node i", LINE_INFO());
			}

			//check
			for (int i = 0; i < 100; i++)
			{
				Assert::AreEqual(tree.countSubtree(tree.findNode(i)), tree.findNode(i)->count, L"count for node i", LINE_INFO());
				Assert::AreEqual(tree.countSubtree(tree.findNode(i)->left), tree.findNode(i)->lcount, L"lcount for node i", LINE_INFO());
				Assert::AreEqual(tree.countSubtree(tree.findNode(i)->right), tree.findNode(i)->rcount, L"rcount for node i", LINE_INFO());
			}

			//now remove rand elements
			for (int i = 0; i < 100; i++)
			{
				int temp = rand() % 100;
				tree.remove(temp);
				stringstream ss;
				for (int j = 0; j < 100; j++)
				{
					bst<int>::bst_node * temp = tree.findNode(j);
					if (temp != nullptr) {
						ss.clear();
						ss << "i is: " << i << " j is: " << j << endl;
						Logger::WriteMessage(ss.str().c_str());
						Assert::AreEqual(tree.countSubtree(temp), temp->count, L"count for node i", LINE_INFO());
						Assert::AreEqual(tree.countSubtree(temp->left), temp->lcount, L"lcount for node i", LINE_INFO());
						Assert::AreEqual(tree.countSubtree(temp->right), temp->rcount, L"rcount for node i", LINE_INFO());
					}
				}

			}

			//check
			for (int i = 0; i < 100; i++)
			{
				bst<int>::bst_node * temp = tree.findNode(i);
				if (temp != nullptr) {
					Assert::AreEqual(tree.countSubtree(temp), temp->count, L"count for node i", LINE_INFO());
					Assert::AreEqual(tree.countSubtree(temp->left), temp->lcount, L"lcount for node i", LINE_INFO());
					Assert::AreEqual(tree.countSubtree(temp->right), temp->rcount, L"rcount for node i", LINE_INFO());
				}
			}

			//new tree for from_vec
			bst<int> *treePtr = new bst<int>();
			vector<int> vec = vector<int>();

			int max = 5;
			for (int i = 0; i < 100; i++)
			{
				int num = max + rand() % max; //pick a num from 0 - 200
				if (num > max) max = num;
				vec.push_back(num);
			}

			treePtr = treePtr->from_sorted_vec(vec, 100);
			cmpVectors(vec, *treePtr->to_vector());

			for (int i = 0; i < max; i++)
			{
				if (treePtr->findNode(i) != nullptr) {
					Assert::AreEqual(treePtr->countSubtree(treePtr->findNode(i)), treePtr->findNode(i)->count, L"count for node i", LINE_INFO());
					Assert::AreEqual(treePtr->countSubtree(treePtr->findNode(i)->left), treePtr->findNode(i)->lcount, L"lcount for node i", LINE_INFO());
					Assert::AreEqual(treePtr->countSubtree(treePtr->findNode(i)->right), treePtr->findNode(i)->rcount, L"rcount for node i", LINE_INFO());
				}
			}


		}

		TEST_METHOD(testGetIth) {
			bst<int> *tree = new bst<int>();
			int x = 0;
			vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };

			x = -1;
			Assert::AreEqual(false, tree->get_ith(x, x), L"out of bounds fail", LINE_INFO());
			x = 0;
			Assert::AreEqual(false, tree->get_ith(x, x), L"out of bounds fail", LINE_INFO());
			x = 1;
			Assert::AreEqual(false, tree->get_ith(x, x), L"out of bounds fail", LINE_INFO());
			x = 2;
			Assert::AreEqual(false, tree->get_ith(x, x), L"out of bounds fail", LINE_INFO());
			x = 3;
			tree->insert(x);	//insert(3)
			tree->get_ith(1, x);	//get the first smallest
			Assert::AreEqual(3, x, L"x isn't right", LINE_INFO());	//should be 3
			x = 4;
			tree->insert(x);	//insert(4)
			tree->get_ith(1, x);	//get the first smallest
			Assert::AreEqual(3, x, L"x isn't right", LINE_INFO());	//should be 3
			tree->get_ith(2, x);	//get the second smallest
			Assert::AreEqual(4, x, L"x isn't right", LINE_INFO());	//should be 4
			x = 2;
			tree->insert(x);	//insert(3)
			tree->get_ith(1, x);	//get the first smallest
			Assert::AreEqual(2, x, L"x isn't right", LINE_INFO());	//should be 3
			tree->get_ith(2, x);	//get the first smallest
			Assert::AreEqual(3, x, L"x isn't right", LINE_INFO());	//should be 3
			tree->get_ith(3, x);	//get the first smallest
			Assert::AreEqual(4, x, L"x isn't right", LINE_INFO());	//should be 3
			tree->~bst();
			tree = tree->from_sorted_vec(vec, 17);

			for (int i = 1; i < 18; i++)
			{
				tree->get_ith(i, x);
				Assert::AreEqual(vec.at(i - 1), x, L"the returnd val isn't the same as vec.i", LINE_INFO());
			}

			tree->get_ith(5, x);
			Assert::AreEqual(55, x, L"the returnd val isn't the same as vec.i", LINE_INFO());
			tree->get_ith(9, x);
			Assert::AreEqual(99, x, L"the returnd val isn't the same as vec.i", LINE_INFO());
		}

		TEST_METHOD(testGEQ) {
			bst<int> *tree = new bst<int>();
			int x = 11;
			vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };

			//empty
			Assert::AreEqual(0, tree->num_geq(3), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_geq(-1), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_geq(0), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_geq(9999), L"empty", LINE_INFO());
			//[11]
			tree->insert(x);
			Assert::AreEqual(1, tree->num_geq(3), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_geq(-1), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_geq(10), L"empty", LINE_INFO());	//boundary
			Assert::AreEqual(1, tree->num_geq(11), L"empty", LINE_INFO());	//boundary
			Assert::AreEqual(0, tree->num_geq(12), L"empty", LINE_INFO());	//boundary
			Assert::AreEqual(0, tree->num_geq(9999), L"empty", LINE_INFO());
			//11
			// 29
			x = 29;
			tree->insert(x);
			Assert::AreEqual(2, tree->num_geq(3), L"empty", LINE_INFO());
			Assert::AreEqual(2, tree->num_geq(-1), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_geq(12), L"empty", LINE_INFO());
			Assert::AreEqual(2, tree->num_geq(10), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_geq(9999), L"empty", LINE_INFO());

			//  11
			//8   29
			//  19
			x = 8;
			tree->insert(x);
			x = 19;
			tree->insert(x);
			Assert::AreEqual(4, tree->num_geq(3), L"empty", LINE_INFO());
			Assert::AreEqual(2, tree->num_geq(12), L"empty", LINE_INFO());
			Assert::AreEqual(3, tree->num_geq(10), L"empty", LINE_INFO());
			Assert::AreEqual(3, tree->num_geq(9), L"empty", LINE_INFO());
			Assert::AreEqual(4, tree->num_geq(8), L"empty", LINE_INFO());
			tree->~bst();

			tree = tree->from_sorted_vec(vec, 17);

			for (int i = 0; i < 17; i++)
			{//you have to match the numbers with the ge function and i
				Assert::AreEqual(17 - i, tree->num_geq(vec.at(i)), L"test", LINE_INFO());
			}

		}

		TEST_METHOD(testLEQ) {
			bst<int> *tree = new bst<int>();
			int x = 11;
			vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };

			//empty
			Assert::AreEqual(0, tree->num_leq(3), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(-1), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(0), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(9999), L"empty", LINE_INFO());
			//[11]
			tree->insert(x);
			Assert::AreEqual(0, tree->num_leq(3), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(-1), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(10), L"empty", LINE_INFO());	//boundary
			Assert::AreEqual(1, tree->num_leq(11), L"empty", LINE_INFO());	//boundary
			Assert::AreEqual(1, tree->num_leq(12), L"empty", LINE_INFO());	//boundary
			Assert::AreEqual(1, tree->num_leq(9999), L"empty", LINE_INFO());
			//11
			// 29
			x = 29;
			tree->insert(x);
			Assert::AreEqual(0, tree->num_leq(3), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(-1), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_leq(12), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(10), L"empty", LINE_INFO());
			Assert::AreEqual(2, tree->num_leq(9999), L"empty", LINE_INFO());

			//  11
			//8   29
			//  19
			x = 8;
			tree->insert(x);
			x = 19;
			tree->insert(x);
			Assert::AreEqual(0, tree->num_leq(3), L"empty", LINE_INFO());
			Assert::AreEqual(2, tree->num_leq(12), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_leq(10), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_leq(9), L"empty", LINE_INFO());
			Assert::AreEqual(1, tree->num_leq(8), L"empty", LINE_INFO());
			Assert::AreEqual(0, tree->num_leq(7), L"empty", LINE_INFO());
			tree->~bst();

			tree = tree->from_sorted_vec(vec, 17);

			for (int i = 0; i < 17; i++)
			{//you have to match the numbers with the ge function and i
				Assert::AreEqual(i + 1, tree->num_leq(vec.at(i)), L"test", LINE_INFO());
			}
		}

		TEST_METHOD(testNumRange) {
			bst<int> *tree = new bst<int>();
			int x = 11;
			vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };
			Assert::AreEqual(0, tree->num_range(0, 1), L"empty check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(-1, 0), L"empty check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(0, 0), L"empty check", LINE_INFO());
			tree->insert(x);
			Assert::AreEqual(0, tree->num_range(12, 12), L"11 check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(10, 10), L"11 check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(0, 10), L"11 check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(12, 20), L"11 check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(0, 0), L"11 check", LINE_INFO());
			Assert::AreEqual(1, tree->num_range(11, 11), L"11 check", LINE_INFO());
			Assert::AreEqual(1, tree->num_range(10, 12), L"11 check", LINE_INFO());
			Assert::AreEqual(1, tree->num_range(10, 11), L"11 check", LINE_INFO());
			Assert::AreEqual(1, tree->num_range(10, 12), L"11 check", LINE_INFO());
			Assert::AreEqual(1, tree->num_range(2, 20), L"11 check", LINE_INFO());
			tree->~bst();
			tree = tree->from_sorted_vec(vec, 17);
			Assert::AreEqual(0, tree->num_range(0, 10), L"full vec check", LINE_INFO());
			Assert::AreEqual(0, tree->num_range(-11, -10), L"full vec check", LINE_INFO());
			Assert::AreEqual(2, tree->num_range(10, 30), L"full vec check", LINE_INFO());
			Assert::AreEqual(3, tree->num_range(115, 117), L"full vec check", LINE_INFO());
			Assert::AreEqual(9, tree->num_range(66, 114), L"full vec check", LINE_INFO());
			Assert::AreEqual(4, tree->num_range(22, 65), L"full vec check", LINE_INFO());
			Assert::AreEqual(5, tree->num_range(22, 66), L"full vec check", LINE_INFO());
			Assert::AreEqual(17, tree->num_range(0, 118), L"full vec check", LINE_INFO());
		}

		void bookKeepCheck(bst<int>* treePtr) {
			bst<int>::bst_node * temp = treePtr->_min_node(treePtr->root);
			int min = (temp != nullptr) ? temp->val : 0;
			temp = treePtr->_max_node(treePtr->root);
			int max = (temp != nullptr) ? temp->val : 0;
			
			for (int i = min; i < max; i++)
			{
				if (treePtr->findNode(i) != nullptr) {
					Assert::AreEqual(treePtr->countSubtree(treePtr->findNode(i)), treePtr->findNode(i)->count, L"count for node i", LINE_INFO());
					Assert::AreEqual(treePtr->countSubtree(treePtr->findNode(i)->left), treePtr->findNode(i)->lcount, L"lcount for node i", LINE_INFO());
					Assert::AreEqual(treePtr->countSubtree(treePtr->findNode(i)->right), treePtr->findNode(i)->rcount, L"rcount for node i", LINE_INFO());
				}
			}
		}
		TEST_METHOD(testBstBalance) {
			bst<int> *tree = new bst<int>();
			int x = 1;
			vector<int> vec;
			tree->insert(x);
			x = 2;
			tree->insert(x);
			Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
			Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
			x = 3;
			tree->insert(x);
			bookKeepCheck(tree);
			Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
			Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
			x = 4;
			tree->insert(x);
			bookKeepCheck(tree);
			Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
			Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());

			//random values
			int max = 5;
			for (int i = 0; i < 100; i++)
			{
				int num = max + rand() % max; //pick a num from 0 - 200
				if (num > max) max = num;
				vec.push_back(num);
			}

			for (int i = 0; i < max; i++)
			{
				if (tree->findNode(i) != nullptr) {
					tree->insert(i);
					bookKeepCheck(tree);
					Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
					Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
				}
			}

			//
			for (int i = 0; i < max; i++)
			{
				if (tree->findNode(i) != nullptr) {
					tree->remove(i);
					bookKeepCheck(tree);
					Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
					Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
				}
			}
			//incrementing values

			for (int i = 0; i < 1000; i++)
			{
				if (tree->findNode(i) != nullptr) {
					tree->insert(i);
					bookKeepCheck(tree);
					Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
					Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
				}
			}

			for (int i = 0; i < 1000; i++)
			{
				if (tree->findNode(i) != nullptr) {
					tree->remove(i);
					bookKeepCheck(tree);
					Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
					Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
				}
			}
			//decrementing values

			for (int i = 1000; i >= 0; i--)
			{
				if (tree->findNode(i) != nullptr) {
					tree->insert(i);
					bookKeepCheck(tree);
					Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
					Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
				}
			}

			for (int i = 1000; i >= 0; i--)
			{
				if (tree->findNode(i) != nullptr) {
					tree->remove(i);
					bookKeepCheck(tree);
					Assert::AreEqual(0, tree->size_balance_check(tree->root), L"size balance check", LINE_INFO());
					Assert::AreEqual(0, tree->bst_rule_check(tree->root), L"bst rule check", LINE_INFO());
				}
			}


		}
	};

	TEST_CLASS(UnitTest2) {

public:
	int cmpVectors(vector<int> expected, vector<int> actual) {
		wchar_t msg[200];
		if (expected.size() != actual.size()) {
			ATLTRACE2(L"Actual size doesn't equal expected. Got %d when expected %d\n", actual.size(), expected.size());
			//Assert::Fail();
			return 0;
		}
		int size = actual.size();
		for (int i = 0; i < size; i++)
		{
			if (expected.at(i) != actual.at(i)) {
				ATLTRACE2(msg, L"vectors not equal at i=%d, expected:%d got:%d\n", i, expected.at(i), actual.at(i));
				Assert::Fail();
				return i; //return the place were it failed
			}
		}
		return -1; //everything passed
	}

	bool isNull(vector<int>* thing) {
		if (thing == nullptr)return true;
		return false;
	}

	TEST_METHOD(testGetIthSLOW) {
		bst<int> *tree = new bst<int>();
		int x = 0;
		vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };

		x = -1;
		Assert::AreEqual(false, tree->get_ith_SLOW(x, x), L"out of bounds fail", LINE_INFO());
		x = 0;
		Assert::AreEqual(false, tree->get_ith_SLOW(x, x), L"out of bounds fail", LINE_INFO());
		x = 1;
		Assert::AreEqual(false, tree->get_ith_SLOW(x, x), L"out of bounds fail", LINE_INFO());
		x = 2;
		Assert::AreEqual(false, tree->get_ith_SLOW(x, x), L"out of bounds fail", LINE_INFO());
		x = 3;
		tree->insert(x);	//insert(3)
		tree->get_ith_SLOW(1, x);	//get the first smallest
		Assert::AreEqual(3, x, L"x isn't right", LINE_INFO());	//should be 3
		x = 4;
		tree->insert(x);	//insert(4)
		tree->get_ith_SLOW(1, x);	//get the first smallest
		Assert::AreEqual(3, x, L"x isn't right", LINE_INFO());	//should be 3
		tree->get_ith_SLOW(2, x);	//get the second smallest
		Assert::AreEqual(4, x, L"x isn't right", LINE_INFO());	//should be 4
		x = 2;
		tree->insert(x);	//insert(3)
		tree->get_ith_SLOW(1, x);	//get the first smallest
		Assert::AreEqual(2, x, L"x isn't right", LINE_INFO());	//should be 3
		tree->get_ith_SLOW(2, x);	//get the first smallest
		Assert::AreEqual(3, x, L"x isn't right", LINE_INFO());	//should be 3
		tree->get_ith_SLOW(3, x);	//get the first smallest
		Assert::AreEqual(4, x, L"x isn't right", LINE_INFO());	//should be 3
		tree->~bst();
		tree = tree->from_sorted_vec(vec, 17);

		for (int i = 1; i < 18; i++)
		{
			tree->get_ith_SLOW(i, x);
			Assert::AreEqual(vec.at(i - 1), x, L"the returnd val isn't the same as vec.i", LINE_INFO());
		}

		tree->get_ith_SLOW(5, x);
		Assert::AreEqual(55, x, L"the returnd val isn't the same as vec.i", LINE_INFO());
		tree->get_ith_SLOW(9, x);
		Assert::AreEqual(99, x, L"the returnd val isn't the same as vec.i", LINE_INFO());
	}

	TEST_METHOD(testGEQ_SLOW) {
		bst<int> *tree = new bst<int>();
		int x = 11;
		vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };

		//empty
		Assert::AreEqual(0, tree->num_geq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_geq_SLOW(-1), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_geq_SLOW(0), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_geq_SLOW(9999), L"empty", LINE_INFO());
		//[11]
		tree->insert(x);
		Assert::AreEqual(1, tree->num_geq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_geq_SLOW(-1), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_geq_SLOW(10), L"empty", LINE_INFO());	//boundary
		Assert::AreEqual(1, tree->num_geq_SLOW(11), L"empty", LINE_INFO());	//boundary
		Assert::AreEqual(0, tree->num_geq_SLOW(12), L"empty", LINE_INFO());	//boundary
		Assert::AreEqual(0, tree->num_geq_SLOW(9999), L"empty", LINE_INFO());
		//11
		// 29
		x = 29;
		tree->insert(x);
		Assert::AreEqual(2, tree->num_geq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(2, tree->num_geq_SLOW(-1), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_geq_SLOW(12), L"empty", LINE_INFO());
		Assert::AreEqual(2, tree->num_geq_SLOW(10), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_geq_SLOW(9999), L"empty", LINE_INFO());

		//  11
		//8   29
		//  19
		x = 8;
		tree->insert(x);
		x = 19;
		tree->insert(x);
		Assert::AreEqual(4, tree->num_geq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(2, tree->num_geq_SLOW(12), L"empty", LINE_INFO());
		Assert::AreEqual(3, tree->num_geq_SLOW(10), L"empty", LINE_INFO());
		Assert::AreEqual(3, tree->num_geq_SLOW(9), L"empty", LINE_INFO());
		Assert::AreEqual(4, tree->num_geq_SLOW(8), L"empty", LINE_INFO());
		tree->~bst();

		tree = tree->from_sorted_vec(vec, 17);

		for (int i = 0; i < 17; i++)
		{//you have to match the numbers with the ge function and i
			Assert::AreEqual(17 - i, tree->num_geq_SLOW(vec.at(i)), L"test", LINE_INFO());
		}

	}

	TEST_METHOD(testLEQ_SLOW) {
		bst<int> *tree = new bst<int>();
		int x = 11;
		vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };

		//empty
		Assert::AreEqual(0, tree->num_leq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(-1), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(0), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(9999), L"empty", LINE_INFO());
		//[11]
		tree->insert(x);
		Assert::AreEqual(0, tree->num_leq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(-1), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(10), L"empty", LINE_INFO());	//boundary
		Assert::AreEqual(1, tree->num_leq_SLOW(11), L"empty", LINE_INFO());	//boundary
		Assert::AreEqual(1, tree->num_leq_SLOW(12), L"empty", LINE_INFO());	//boundary
		Assert::AreEqual(1, tree->num_leq_SLOW(9999), L"empty", LINE_INFO());
		//11
		// 29
		x = 29;
		tree->insert(x);
		Assert::AreEqual(0, tree->num_leq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(-1), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_leq_SLOW(12), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(10), L"empty", LINE_INFO());
		Assert::AreEqual(2, tree->num_leq_SLOW(9999), L"empty", LINE_INFO());

		//  11
		//8   29
		//  19
		x = 8;
		tree->insert(x);
		x = 19;
		tree->insert(x);
		Assert::AreEqual(0, tree->num_leq_SLOW(3), L"empty", LINE_INFO());
		Assert::AreEqual(2, tree->num_leq_SLOW(12), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_leq_SLOW(10), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_leq_SLOW(9), L"empty", LINE_INFO());
		Assert::AreEqual(1, tree->num_leq_SLOW(8), L"empty", LINE_INFO());
		Assert::AreEqual(0, tree->num_leq_SLOW(7), L"empty", LINE_INFO());
		tree->~bst();

		tree = tree->from_sorted_vec(vec, 17);

		for (int i = 0; i < 17; i++)
		{//you have to match the numbers with the ge function and i
			Assert::AreEqual(i + 1, tree->num_leq_SLOW(vec.at(i)), L"test", LINE_INFO());
		}
	}

	TEST_METHOD(testNumRange_SLOW) {
		bst<int> *tree = new bst<int>();
		int x = 11;
		vector<int> vec = { 11,22,33,44,55,66,77,88,99,100,111,112,113,114,115,116,117 };
		Assert::AreEqual(0, tree->num_range_SLOW(0, 1), L"empty check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(-1, 0), L"empty check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(0, 0), L"empty check", LINE_INFO());
		tree->insert(x);
		Assert::AreEqual(0, tree->num_range_SLOW(12, 12), L"11 check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(10, 10), L"11 check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(0, 10), L"11 check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(12, 20), L"11 check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(0, 0), L"11 check", LINE_INFO());
		Assert::AreEqual(1, tree->num_range_SLOW(11, 11), L"11 check", LINE_INFO());
		Assert::AreEqual(1, tree->num_range_SLOW(10, 12), L"11 check", LINE_INFO());
		Assert::AreEqual(1, tree->num_range_SLOW(10, 11), L"11 check", LINE_INFO());
		Assert::AreEqual(1, tree->num_range_SLOW(10, 12), L"11 check", LINE_INFO());
		Assert::AreEqual(1, tree->num_range_SLOW(2, 20), L"11 check", LINE_INFO());
		tree->~bst();
		tree = tree->from_sorted_vec(vec, 17);
		Assert::AreEqual(0, tree->num_range_SLOW(0, 10), L"full vec check", LINE_INFO());
		Assert::AreEqual(0, tree->num_range_SLOW(-11, -10), L"full vec check", LINE_INFO());
		Assert::AreEqual(2, tree->num_range_SLOW(10, 30), L"full vec check", LINE_INFO());
		Assert::AreEqual(3, tree->num_range_SLOW(115, 117), L"full vec check", LINE_INFO());
		Assert::AreEqual(9, tree->num_range_SLOW(66, 114), L"full vec check", LINE_INFO());
		Assert::AreEqual(4, tree->num_range_SLOW(22, 65), L"full vec check", LINE_INFO());
		Assert::AreEqual(5, tree->num_range_SLOW(22, 66), L"full vec check", LINE_INFO());
		Assert::AreEqual(17, tree->num_range_SLOW(0, 118), L"full vec check", LINE_INFO());
	}
	};
}