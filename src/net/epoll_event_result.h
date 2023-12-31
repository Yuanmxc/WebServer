#ifndef EPOLLEVENTRESULT_H_
#define EPOLLEVENTRESULT_H_

#include <memory>
#include <stdexcept>

#include "../base/nocopy.h"
#include "epoll_event.h"
namespace ws {
class EpollEvent_Result final : public Nocopy {
    friend class Epoll;

   public:
    explicit EpollEvent_Result(int len)
        : array(new EpollEvent[len]), Available_length(0), All_length(len) {}

    size_t size() const { return Available_length; }
    EpollEvent& at(size_t i) {
        if (i > Available_length) {
            throw std::out_of_range(
                "'EpollEvent_Result : at' : Out of bounds.");
        } else {
            return array[i];
        }
    }
    const EpollEvent& operator[](size_t i) const {
        if (i > Available_length)
            throw std::out_of_range("'EpollEvent_Result : []' Out of Bounds.");
        return array[i];
    }
    EpollEvent& operator[](size_t i) {
        return const_cast<EpollEvent&>(
            static_cast<const EpollEvent_Result&>(*this)[i]);
    }
    ~EpollEvent_Result() {}

   private:
    std::unique_ptr<EpollEvent[]> array;
    size_t Available_length;
    size_t All_length;
};
}  // namespace ws

#endif