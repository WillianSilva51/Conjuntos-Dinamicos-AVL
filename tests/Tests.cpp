#include "gtest/gtest.h"
#include <sstream>  // Para std::stringstream
#include <iostream> // Para std::streambuf
#include <vector>
#include <algorithm> // Para std::sort, std::set_union etc. para verificação
#include <stdexcept> // Para std::runtime_error

// Assume que Node.hpp e Set.hpp estão acessíveis.
// Se estiverem num diretório específico como 'src', ajuste o caminho de inclusão
// ou garanta que os caminhos de inclusão do seu sistema de compilação estão configurados corretamente.
#include "set/Set.hpp" // Isto deve incluir Node.hpp conforme a sua estrutura

// --- Testes Node ---
TEST(NodeTest, ConstructorInitializesCorrectly)
{
    Node<int> node1(10);
    EXPECT_EQ(node1.key, 10);
    EXPECT_EQ(node1.height, 1); // Altura padrão
    EXPECT_EQ(node1.left, nullptr);
    EXPECT_EQ(node1.right, nullptr);

    Node<int> node2(20, 2, nullptr, nullptr);
    EXPECT_EQ(node2.key, 20);
    EXPECT_EQ(node2.height, 2);
    EXPECT_EQ(node2.left, nullptr);
    EXPECT_EQ(node2.right, nullptr);

    Node<int> left_child(5);
    Node<int> right_child(15);
    Node<int> parent_node(10, 3, &left_child, &right_child);
    EXPECT_EQ(parent_node.key, 10);
    EXPECT_EQ(parent_node.height, 3);
    EXPECT_EQ(parent_node.left, &left_child);
    EXPECT_EQ(parent_node.right, &right_child);
    EXPECT_EQ(parent_node.left->key, 5);
    EXPECT_EQ(parent_node.right->key, 15);
}

// --- Testes Set (Árvore AVL) ---
class AVLSetTest : public ::testing::Test
{
protected:
    Set<int> s; // Conjunto vazio padrão para cada teste

    // Auxiliar para obter a saída de string de uma função de impressão
    template <typename Func>
    std::string getPrintOutput(Set<int> &set_to_print, Func print_func)
    {
        std::stringstream ss;
        std::streambuf *old_cout = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf()); // Redirecionar cout

        (set_to_print.*print_func)(); // Chamar o ponteiro da função membro

        std::cout.rdbuf(old_cout); // Restaurar cout
        return ss.str();
    }

    // Auxiliar para verificar elementos no conjunto (usando expectativa de travessia em ordem)
    void verifyElements(const Set<int> &set_to_check, std::vector<int> expected_elements)
    {
        std::sort(expected_elements.begin(), expected_elements.end());

        std::stringstream ss_expected;
        for (size_t i = 0; i < expected_elements.size(); ++i)
        {
            ss_expected << expected_elements[i] << (i == expected_elements.size() - 1 ? "" : " ");
        }
        if (!expected_elements.empty())
            ss_expected << " "; // Espaço final de printInOrder

        // Usar uma referência não-const para chamar printInOrder não-const
        Set<int> temp_set = set_to_check; // Requer um construtor de cópia funcional

        std::string actual_output = getPrintOutput(temp_set, static_cast<void (Set<int>::*)()>(&Set<int>::printInOrder));
        EXPECT_EQ(actual_output, ss_expected.str()) << "Falha na correspondência da saída de printInOrder.";
        EXPECT_EQ(temp_set.size(), expected_elements.size()) << "Falha na correspondência do tamanho do conjunto.";
        for (int val : expected_elements)
        {
            EXPECT_TRUE(temp_set.contains(val)) << "Elemento esperado " << val << " não encontrado.";
        }
    }
};

// --- Testes de Construtor ---
TEST_F(AVLSetTest, DefaultConstructor)
{
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST_F(AVLSetTest, InitializerListConstructor)
{
    Set<int> s_list = {10, 20, 5, 15, 5}; // 5 duplicado
    EXPECT_EQ(s_list.size(), 4);
    EXPECT_TRUE(s_list.contains(10));
    EXPECT_TRUE(s_list.contains(20));
    EXPECT_TRUE(s_list.contains(5));
    EXPECT_TRUE(s_list.contains(15));
    EXPECT_FALSE(s_list.empty());
    verifyElements(s_list, {5, 10, 15, 20});
}

TEST_F(AVLSetTest, CopyConstructor)
{
    s.insert(10);
    s.insert(5);
    s.insert(15);

    Set<int> s_copy(s);
    EXPECT_EQ(s_copy.size(), 3);
    EXPECT_TRUE(s_copy.contains(10));
    EXPECT_TRUE(s_copy.contains(5));
    EXPECT_TRUE(s_copy.contains(15));
    EXPECT_FALSE(s_copy.empty());

    // Modificar original, cópia deve ser independente
    s.insert(20);
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s_copy.size(), 3);
    EXPECT_FALSE(s_copy.contains(20));

    verifyElements(s_copy, {5, 10, 15});
}

TEST_F(AVLSetTest, CopyConstructorEmpty)
{
    Set<int> s_empty;
    Set<int> s_copy(s_empty);
    EXPECT_TRUE(s_copy.empty());
    EXPECT_EQ(s_copy.size(), 0);
}

// --- Operações Básicas ---
TEST_F(AVLSetTest, SizeAndEmpty)
{
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);

    s.insert(10);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);

    s.insert(20);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2);

    s.insert(10); // Duplicado
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2); // Tamanho não deve mudar

    s.erase(10);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);

    s.erase(20);
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST_F(AVLSetTest, Clear)
{
    s.insert(10);
    s.insert(20);
    s.insert(5);
    ASSERT_FALSE(s.empty());
    ASSERT_EQ(s.size(), 3);

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_FALSE(s.contains(10)); // Garantir que os elementos desapareceram

    s.clear(); // Limpar um conjunto já vazio
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST_F(AVLSetTest, Swap)
{
    Set<int> s1 = {1, 2, 3};
    Set<int> s2 = {10, 20};

    s1.swap(s2);

    EXPECT_EQ(s1.size(), 2);
    EXPECT_TRUE(s1.contains(10));
    EXPECT_TRUE(s1.contains(20));
    EXPECT_FALSE(s1.contains(1));

    EXPECT_EQ(s2.size(), 3);
    EXPECT_TRUE(s2.contains(1));
    EXPECT_TRUE(s2.contains(2));
    EXPECT_TRUE(s2.contains(3));
    EXPECT_FALSE(s2.contains(10));

    verifyElements(s1, {10, 20});
    verifyElements(s2, {1, 2, 3});
}

// --- Inserção e Rotações AVL ---
TEST_F(AVLSetTest, InsertBasic)
{
    s.insert(10);
    EXPECT_TRUE(s.contains(10));
    EXPECT_EQ(s.size(), 1);

    s.insert(5); // Inserir menor
    EXPECT_TRUE(s.contains(5));
    EXPECT_EQ(s.size(), 2);

    s.insert(15); // Inserir maior
    EXPECT_TRUE(s.contains(15));
    EXPECT_EQ(s.size(), 3);

    verifyElements(s, {5, 10, 15});
}

TEST_F(AVLSetTest, InsertDuplicates)
{
    s.insert(10);
    s.insert(10);
    s.insert(10);
    EXPECT_EQ(s.size(), 1);
    EXPECT_TRUE(s.contains(10));
}

TEST_F(AVLSetTest, InsertCausesRightRotation_LL)
{
    s.insert(30);
    s.insert(20);
    s.insert(10); // Caso LL
    EXPECT_EQ(s.size(), 3);
    verifyElements(s, {10, 20, 30});
    // Estrutura esperada: raiz=20, esquerda=10, direita=30
}

TEST_F(AVLSetTest, InsertCausesLeftRotation_RR)
{
    s.insert(10);
    s.insert(20);
    s.insert(30); // Caso RR
    EXPECT_EQ(s.size(), 3);
    verifyElements(s, {10, 20, 30});
    // Estrutura esperada: raiz=20, esquerda=10, direita=30
}

TEST_F(AVLSetTest, InsertCausesLeftRightRotation_LR)
{
    s.insert(30);
    s.insert(10);
    s.insert(20); // Caso LR
    EXPECT_EQ(s.size(), 3);
    verifyElements(s, {10, 20, 30});
    // Estrutura esperada: raiz=20, esquerda=10, direita=30
}

TEST_F(AVLSetTest, InsertCausesRightLeftRotation_RL)
{
    s.insert(10);
    s.insert(30);
    s.insert(20); // Caso RL
    EXPECT_EQ(s.size(), 3);
    verifyElements(s, {10, 20, 30});
    // Estrutura esperada: raiz=20, esquerda=10, direita=30
}

TEST_F(AVLSetTest, InsertComplexSequence)
{
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    s.insert(50);
    s.insert(25);

    EXPECT_EQ(s.size(), 6);
    verifyElements(s, {10, 20, 25, 30, 40, 50});
}

// --- Remoção e Rebalanceamento AVL ---
TEST_F(AVLSetTest, EraseNonExistent)
{
    s.insert(10);
    s.insert(20);
    s.erase(15); // Não está no conjunto
    EXPECT_EQ(s.size(), 2);
    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(20));
}

TEST_F(AVLSetTest, EraseFromEmptySet)
{
    s.erase(10);
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());
}

TEST_F(AVLSetTest, EraseLeafNode)
{
    s = {10, 5, 15}; // Árvore balanceada
    s.erase(5);      // Remover folha
    EXPECT_EQ(s.size(), 2);
    EXPECT_FALSE(s.contains(5));
    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(15));
    verifyElements(s, {10, 15});
}

TEST_F(AVLSetTest, EraseNodeWithOneLeftChild)
{
    s = {10, 5, 15, 3}; // 5 tem filho esquerdo 3
    s.erase(5);
    EXPECT_EQ(s.size(), 3);
    EXPECT_FALSE(s.contains(5));
    EXPECT_TRUE(s.contains(3));
    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(15));
    verifyElements(s, {3, 10, 15});
}

TEST_F(AVLSetTest, EraseNodeWithOneRightChild)
{
    s = {10, 5, 15, 7}; // 5 tem filho direito 7
    s.erase(5);
    EXPECT_EQ(s.size(), 3);
    EXPECT_FALSE(s.contains(5));
    EXPECT_TRUE(s.contains(7));
    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(15));
    verifyElements(s, {7, 10, 15});
}

TEST_F(AVLSetTest, EraseNodeWithTwoChildren_SuccessorIsLeaf)
{
    s = {20, 10, 30, 5, 15, 25, 35, 12}; // 10 tem dois filhos (5,15(L:12)), sucessor de 10 é 12 (folha)
    s.erase(10);                         // Chave do Nó 10 torna-se 12, nó 12 é removido.
    EXPECT_EQ(s.size(), 7);
    EXPECT_FALSE(s.contains(10));
    EXPECT_TRUE(s.contains(12)); // Nó original 10 agora contém 12
    verifyElements(s, {5, 12, 15, 20, 25, 30, 35});
}

TEST_F(AVLSetTest, EraseNodeWithTwoChildren_SuccessorHasRightChild)
{
    s.clear();
    s = {20, 10, 30, 5, 15, 25, 35, 12, 17, 18};
    // Elementos iniciais: {5, 10, 12, 15, 17, 18, 20, 25, 30, 35}
    // Objetivo: remover nó 15.
    // Sucessor é 17. Nó 17 tem filho direito 18.

    s.erase(15);
    // Chave do nó 15 torna-se 17. Nó original 17 é removido.
    // Nó 18 (filho direito do nó original 17) deve tomar o lugar do nó original 17.
    EXPECT_EQ(s.size(), 9);
    EXPECT_FALSE(s.contains(15));
    EXPECT_TRUE(s.contains(17)); // A chave 17 agora existe onde 15 estava.
    EXPECT_TRUE(s.contains(18));
    verifyElements(s, {5, 10, 12, 17, 18, 20, 25, 30, 35});
}

TEST_F(AVLSetTest, EraseRoot)
{
    s = {10, 5, 15};
    s.erase(10); // Remover raiz
    EXPECT_EQ(s.size(), 2);
    EXPECT_FALSE(s.contains(10));
    // 5 ou 15 podem ser a nova raiz dependendo da lógica do sucessor
    verifyElements(s, {5, 15});
}

TEST_F(AVLSetTest, EraseCausesRebalance_SimpleRightRotation_L_Case)
{
    s.clear();
    s = {20, 10, 30, 5}; // Raiz 20, E:10(E:5), D:30. Balanceado.
    s.erase(30);         // Removendo 30.
                         // Nó 20 fica desbalanceado (bal -2). Seu filho esquerdo 10 tem balanço <= 0.
                         // Requer rotação simples à direita em 20. Nova raiz 10.
                         // Árvore:   10
                         //        /  \
                 //       5   20
    EXPECT_EQ(s.size(), 3);
    verifyElements(s, {5, 10, 20});
}

TEST_F(AVLSetTest, EraseCausesRebalance_SimpleLeftRotation_R_Case)
{
    s.clear();
    s = {10, 5, 20, 25}; // Raiz 10, E:5, D:20(D:25). Balanceado.
    s.erase(5);          // Removendo 5.
                         // Nó 10 fica desbalanceado (bal 2). Seu filho direito 20 tem balanço >= 0.
                         // Requer rotação simples à esquerda em 10. Nova raiz 20.
                         // Árvore:   20
                         //        /  \
                      //       10  25
    EXPECT_EQ(s.size(), 3);
    verifyElements(s, {10, 20, 25});
}

// --- Operações de Busca ---
TEST_F(AVLSetTest, Contains)
{
    s.insert(10);
    s.insert(20);
    s.insert(5);

    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(5));
    EXPECT_TRUE(s.contains(20));
    EXPECT_FALSE(s.contains(15));
    EXPECT_FALSE(s.contains(0));
}

TEST_F(AVLSetTest, ContainsOnEmptySet)
{
    EXPECT_FALSE(s.contains(10));
}

// --- Min/Max ---
TEST_F(AVLSetTest, MinimumMaximum)
{
    s = {10, 20, 5, 30, 1};
    EXPECT_EQ(s.minimum(), 1);
    EXPECT_EQ(s.maximum(), 30);

    s.insert(100);
    s.insert(0);
    EXPECT_EQ(s.minimum(), 0);
    EXPECT_EQ(s.maximum(), 100);
}

TEST_F(AVLSetTest, MinimumMaximum_SingleElement)
{
    s.insert(42);
    EXPECT_EQ(s.minimum(), 42);
    EXPECT_EQ(s.maximum(), 42);
}

TEST_F(AVLSetTest, MinimumMaximum_ThrowsOnEmpty)
{
    EXPECT_THROW(s.minimum(), std::runtime_error);
    EXPECT_THROW(s.maximum(), std::runtime_error);
}

// --- Sucessor/Predecessor ---
TEST_F(AVLSetTest, Successor)
{
    s = {10, 5, 15, 3, 7, 12, 17, 6, 8};
    // Elementos: 3, 5, 6, 7, 8, 10, 12, 15, 17
    EXPECT_EQ(s.successor(3), 5);
    EXPECT_EQ(s.successor(5), 6);
    EXPECT_EQ(s.successor(8), 10);
    EXPECT_EQ(s.successor(10), 12);
    EXPECT_EQ(s.successor(15), 17);
    EXPECT_THROW(s.successor(17), std::runtime_error); // Sem sucessor
}

TEST_F(AVLSetTest, Predecessor)
{
    s = {10, 5, 15, 3, 7, 12, 17, 6, 8};
    // Elementos: 3, 5, 6, 7, 8, 10, 12, 15, 17
    EXPECT_EQ(s.predecessor(5), 3);
    EXPECT_EQ(s.predecessor(6), 5);
    EXPECT_EQ(s.predecessor(10), 8);
    EXPECT_EQ(s.predecessor(12), 10);
    EXPECT_EQ(s.predecessor(17), 15);
    EXPECT_THROW(s.predecessor(3), std::runtime_error); // Sem predecessor
}

TEST_F(AVLSetTest, SuccessorPredecessor_ThrowsOnEmptyOrNotFound)
{
    EXPECT_THROW(s.successor(10), std::runtime_error);   // Vazio
    EXPECT_THROW(s.predecessor(10), std::runtime_error); // Vazio
    s.insert(20);
    EXPECT_THROW(s.successor(10), std::runtime_error);   // Não encontrado
    EXPECT_THROW(s.predecessor(30), std::runtime_error); // Não encontrado
}

// --- Operações de Conjunto ---
TEST_F(AVLSetTest, Union)
{
    Set<int> s1 = {1, 2, 3};
    Set<int> s2 = {3, 4, 5};
    Set<int> result = s1.Union(s2);
    verifyElements(result, {1, 2, 3, 4, 5});
    EXPECT_EQ(result.size(), 5);

    result = s1 + s2; // Operator+
    verifyElements(result, {1, 2, 3, 4, 5});
}

TEST_F(AVLSetTest, UnionWithEmpty)
{
    Set<int> s1 = {1, 2, 3};
    Set<int> s_empty;
    Set<int> result1 = s1.Union(s_empty);
    verifyElements(result1, {1, 2, 3});

    Set<int> result2 = s_empty.Union(s1);
    verifyElements(result2, {1, 2, 3});
}

TEST_F(AVLSetTest, Intersection)
{
    Set<int> s1 = {1, 2, 3, 4};
    Set<int> s2 = {3, 4, 5, 6};
    Set<int> result = s1.Intersection(s2);
    verifyElements(result, {3, 4});
    EXPECT_EQ(result.size(), 2);

    result = s1 * s2; // Operator*
    verifyElements(result, {3, 4});
}

TEST_F(AVLSetTest, IntersectionNoOverlap)
{
    Set<int> s1 = {1, 2};
    Set<int> s2 = {3, 4};
    Set<int> result = s1.Intersection(s2);
    EXPECT_TRUE(result.empty());
}

TEST_F(AVLSetTest, IntersectionWithEmpty)
{
    Set<int> s1 = {1, 2, 3};
    Set<int> s_empty;
    Set<int> result = s1.Intersection(s_empty);
    EXPECT_TRUE(result.empty());
    result = s_empty.Intersection(s1);
    EXPECT_TRUE(result.empty());
}

TEST_F(AVLSetTest, Difference)
{
    Set<int> s1 = {1, 2, 3, 4};
    Set<int> s2 = {3, 4, 5, 6};
    Set<int> result = s1.Difference(s2); // s1 - s2
    verifyElements(result, {1, 2});
    EXPECT_EQ(result.size(), 2);

    result = s1 - s2; // Operator-
    verifyElements(result, {1, 2});

    Set<int> result_rev = s2.Difference(s1); // s2 - s1
    verifyElements(result_rev, {5, 6});
}

TEST_F(AVLSetTest, DifferenceWithEmpty)
{
    Set<int> s1 = {1, 2, 3};
    Set<int> s_empty;
    Set<int> result1 = s1.Difference(s_empty);
    verifyElements(result1, {1, 2, 3});

    Set<int> result2 = s_empty.Difference(s1);
    EXPECT_TRUE(result2.empty());
}

// --- Funções de Impressão ---
TEST_F(AVLSetTest, PrintInOrder)
{
    s = {10, 5, 15, 3, 7};
    // Esperado: 3 5 7 10 15
    std::string output = getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printInOrder));
    EXPECT_EQ(output, "3 5 7 10 15 ");
}

TEST_F(AVLSetTest, PrintPreOrder)
{
    s = {10, 5, 15, 3, 7, 12, 17}; // Balanceado: 10 é raiz
    // Esperado para 10 (E:5(E:3 D:7) D:15(E:12 D:17)):
    // 10 5 3 7 15 12 17
    std::string output = getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printPreOrder));
    EXPECT_EQ(output, "10 5 3 7 15 12 17 ");
}

TEST_F(AVLSetTest, PrintPostOrder)
{
    s = {10, 5, 15, 3, 7, 12, 17};
    // Esperado para 10 (E:5(E:3 D:7) D:15(E:12 D:17)):
    // 3 7 5 12 17 15 10
    std::string output = getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printPostOrder));
    EXPECT_EQ(output, "3 7 5 12 17 15 10 ");
}

TEST_F(AVLSetTest, PrintLarge_LevelOrder)
{
    s = {10, 5, 15, 3, 7, 12, 17};
    // Esperado (Ordem por nível): 10 5 15 3 7 12 17
    std::string output = getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printLarge));
    EXPECT_EQ(output, "10 5 15 3 7 12 17 ");
}

TEST_F(AVLSetTest, PrintEmptySet)
{
    EXPECT_EQ(getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printInOrder)), "");
    EXPECT_EQ(getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printPreOrder)), "");
    EXPECT_EQ(getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printPostOrder)), "");
    EXPECT_EQ(getPrintOutput(s, static_cast<void (Set<int>::*)()>(&Set<int>::printLarge)), "");
}