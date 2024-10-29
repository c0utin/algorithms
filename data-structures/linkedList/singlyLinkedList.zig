const std = @import("std");
const Allocator = std.mem.Allocator;

const LL = struct {
    head: ?*Node,
    tail: ?*Node,
    count: usize,
    allocator: Allocator,

    const Node = struct {
        data: i32,
        next: ?*Node,
    };

    pub fn new(allocator: Allocator) LL {
        return .{
            .head = null,
            .tail = null,
            .count = 0,
            .allocator = allocator,
        };
    }

    pub fn destroy(self: *LL) void {
        var curr = self.head;
        while (curr) |c| {
            const next = c.next;
            self.allocator.destroy(c);
            curr = next;
        }
        self.head = null;
        self.tail = null;
        self.count = 0;
    }

    pub fn add_by_index(self: *LL, data: i32, index: usize) !void {
        if (index > self.count) {
            return error.IndexOutOfBounds;
        }

        var new_node = try self.allocator.create(Node);
        new_node.* = Node{ .data = data, .next = null };

        if (index == 0) {
            new_node.next = self.head;
            self.head = new_node;
            if (self.count == 0) {
                self.tail = new_node;
            }
        } else {
            var curr = self.head;
            var prev: ?*Node = null;

            for (index) |_| {
                if (curr == null) {
                    return error.IndexOutOfBounds;
                }
                prev = curr;
                curr = curr.?.next;
            }

            if (prev) |p| {
                p.next = new_node;
            }
            new_node.next = curr;

            if (new_node.next == null) {
                self.tail = new_node;
            }
        }

        self.count += 1;
    }

    pub fn show(self: *LL) void {
        var curr = self.head;
        while (curr) |c| {
            const next = c.next;
            std.debug.print("{}", .{c.data});
            curr = next;
        }
    }
};

// TESTS

test "Linked List" {
    const allocator = std.heap.page_allocator;
    var list = LL.new(allocator);

    try list.add_by_index(6, 0);
    try list.add_by_index(420, 1);
    try list.add_by_index(9, 1);
    try list.add_by_index(1337, 2);
    list.show();
    list.destroy();
}
