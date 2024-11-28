#include "vm/frame.h"        // Định nghĩa các hàm và cấu trúc quản lý khung.
#include "vm/page.h"         // Để kết nối khung với trang.
#include "threads/palloc.h"  // Sử dụng hàm cấp phát bộ nhớ `palloc_get_page`.
#include "threads/thread.h"  // Để truy cập thông tin thread.
#include "threads/malloc.h"  // Để cấp phát bộ nhớ cho `struct frame`.
#include "threads/synch.h"   // Sử dụng semaphore hoặc lock để đồng bộ.
#include <list.h>            // Sử dụng danh sách liên kết cho Frame Table.
#include <stdbool.h>         // Kiểu boolean.


//Quản lý danh sách khung:    
//Thêm danh sách khung frame_table vào frame.c.
static struct list frame_table;
//    Hàm quản lý khung:
//Khởi tạo Frame Table:
void frame_table_init(void) {
    list_init(&frame_table);
}
//Cấp phát khung:
struct frame *frame_alloc(struct page *page) {
    void *kaddr = palloc_get_page(PAL_USER);
    if (kaddr == NULL) {
        // Thay thế khung nếu không còn bộ nhớ.
        return frame_evict();
    }

    struct frame *frame = malloc(sizeof(struct frame));
    frame->kaddr = kaddr;
    frame->page = page;
    list_push_back(&frame_table, &frame->elem);
    return frame;
}
//Giải phóng khung:
void frame_free(struct frame *frame) {
    palloc_free_page(frame->kaddr);
    list_remove(&frame->elem);
    free(frame);
}
//Thay thế khung (Eviction):
struct frame *frame_evict(void) {
    // Áp dụng thuật toán thay thế khung (ví dụ: LRU).
    struct list_elem *e = list_pop_front(&frame_table);
    struct frame *victim = list_entry(e, struct frame, elem);
    // Đẩy khung vào swap trước khi giải phóng.
    swap_out(victim->page);
    frame_free(victim);
    return frame_alloc(NULL); // Cấp phát lại khung mới.
}
