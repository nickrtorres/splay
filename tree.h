#ifndef TREE_H_
#define TREE_H_

#include <optional>
#include <memory>
#include <variant>

struct Empty {};

template <typename T>
class Tree;

template <typename T>
class Node;

template <typename T>
using TreePtr = std::shared_ptr<Tree<T>>;

/*!
 * A NodePtr upholds the invariants of a BinaryTree.
 * The |value| is immutable once it is in the tree.
 */
template <typename T>
using NodePtr = std::shared_ptr<const Node<T>>;

/*!
 * Inspired by mozilla's [Variant] example.
 *
 * [Variant]: https://github.com/mozilla/gecko-dev/blob/master/mfbt/Variant.h#L507
 */
template <typename T>
class Node
{
    T mValue;
    TreePtr<T> mLeft;
    TreePtr<T> mRight;

public:
    Node(T &&value, TreePtr<T> left, TreePtr<T> right)
    : mValue(std::move(value))
    , mLeft(left)
    , mRight(right) {}

    const T & Value() const
    {
        return mValue;
    }
};

template <typename T>
class Tree
{
    std::variant<Empty, NodePtr<T>> mVariant;

public:
    Tree() = default;

    void Insert(T &&t)
    {
        auto current = std::optional<NodePtr<T>> {};
        if (std::holds_alternative<NodePtr<T>>(this->mVariant)) {
            current = std::get<NodePtr<T>>(this->mVariant);
        }

        if (!current) {
            this->mVariant = NodePtr<T>{ new Node<T> {std::move(t), nullptr, nullptr} };
            return;
        }

        // GOAL: std::visit
    }

    // TODO: const correctness
    std::optional<NodePtr<T>> Root()
    {
        auto root = std::optional<NodePtr<T>> {};
        if (std::holds_alternative<NodePtr<T>>(this->mVariant)) {
            root = std::get<NodePtr<T>>(this->mVariant);
        }

        return root;
    }

    // TODO: const correctness
    //       ...and maybe delete
    std::optional<T> RootValue()
    {
        auto root = std::optional<T> {};
        if (std::holds_alternative<NodePtr<T>>(this->mVariant)) {
            root = std::get<NodePtr<T>>(this->mVariant)->Value();
        }

        return root;
    }
};

#endif /* TREE_H_ */
