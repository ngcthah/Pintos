#include "vm/page.h"         // Định nghĩa các cấu trúc và hàm của page.
#include "threads/thread.h"  // Để truy cập thread và SPT của từng thread.
#include "threads/malloc.h"  // Để cấp phát bộ nhớ cho cấu trúc page.
#include "threads/vaddr.h"   // Các macro xử lý địa chỉ ảo, ví dụ: `pg_round_down`.
#include <hash.h>            // Cấu trúc và hàm hash table.
#include <stdbool.h>         // Định nghĩa kiểu bool.
#include <stdint.h>          // Định nghĩa các kiểu dữ liệu uint32_t, uint64_t.

//Hàm quản lý SPT trong page.c:
//Khởi tạo và hủy SPT:
void spt_init(struct hash *spt) {
    hash_init(spt, page_hash, page_less, NULL);
}

void spt_destroy(struct hash *spt) {
    hash_destroy(spt, page_destroy);
}
//Thêm trang:
bool spt_add_page(struct hash *spt, struct page *page) {
    return hash_insert(spt, &page->hash_elem) == NULL;
}
//Tìm trang:
struct page *spt_find_page(struct hash *spt, void *vaddr) {
    struct page p;
    p.vaddr = vaddr;
    struct hash_elem *e = hash_find(spt, &p.hash_elem);
    return e != NULL ? hash_entry(e, struct page, hash_elem) : NULL;
}
