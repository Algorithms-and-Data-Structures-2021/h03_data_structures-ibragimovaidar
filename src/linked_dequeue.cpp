#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  if (size_ == 0){
    back_ = new DoublyNode(e, nullptr, nullptr);
    front_ = back_;
  }
  if (size_ > 0){
    auto* new_back = new DoublyNode(e, nullptr, back_);
    back_->previous = new_back;
    back_ = new_back;
  }

  size_++;
}

void LinkedDequeue::EnqueueFront(Element e) {
  if (size_ == 0){
    back_ = new DoublyNode(e, nullptr, nullptr);
    front_ = back_;
  }
  if (size_ > 0){
    auto* new_front = new DoublyNode(e, front_, nullptr);
    front_->next = new_front;
    front_ = new_front;
  }

  size_++;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  auto* dequeued_node = front_;

  if (size_ == 1) {
    delete dequeued_node;
    front_ = nullptr;
    back_ = nullptr;
    size_--;
    return;
  }

  front_->previous->next = nullptr;
  front_ = front_->previous;
  delete dequeued_node;
  size_--;
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  auto* dequeued_node = back_;

  if (size_ == 1){
    delete dequeued_node;
    back_ = nullptr;
    front_ = nullptr;
    size_--;
    return;
  }

  back_->next->previous = nullptr;
  back_ = back_->next;
  delete dequeued_node;
  size_--;
}

void LinkedDequeue::Clear() {
  while (size_ > 0){
    DequeueBack();
  }
  front_ = nullptr;
  back_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
