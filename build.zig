const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const tests_sources = [_][]const u8{"data-structures/linkedList/singlyLinkedList.zig"};

    const test_step = b.step("test", "Run tests");

    for (tests_sources) |test_source| {
        const exe_tests = b.addTest(.{
            .root_source_file = b.path(test_source),
            .target = target,
            .optimize = optimize,
        });

        const run_exe_tests = b.addRunArtifact(exe_tests);
        test_step.dependOn(&run_exe_tests.step);
    }
}
