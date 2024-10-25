const std = @import("std");

const Node = struct {
    data: i8,
    next: ?*Node = null,

    pub fn new(allocator: *std.mem.Allocator, data: i8) !*Node {
        const node = try allocator.create(Node);
        node.* = Node{
            .data = data,
            .next = undefined,
        };

        return node;
    }

    pub fn destroy(self: *@This(), allocator: *std.mem.Allocator) void {
        allocator.destroy(self);
    }
};

test "Singly Linked List" {
    var allocator = std.testing.allocator;
    const node = try Node.new(&allocator, 8);
    std.debug.print("test {}", .{node.data});
    node.destroy(&allocator);
}
