const std = @import("std");
const zcc = @import("compile_commands.zig");

const c_flags = [_][]const u8{
    "-Wall",
    "-Wextra",
};

// Listing files manually are honestly easier than doing a recursive listing algorithm
const c_source_files = [_][]const u8{
    "./src/main.c",
};

pub fn buildWithLocalRaylib(b: *std.Build, optimization: std.builtin.OptimizeMode, target: std.Build.ResolvedTarget) *std.Build.Step.Compile {
    // The reason raylib is an option:
    // I am still creating many aspects of the engine. Starting with simple stuff like arrays
    // and actual structures containing level data and beatmap data. Up until everything can be parsed, raylib will not be used.
    // Hence no need to actually compile and link raylib. This will be removed once engine is ready to work with a graphics library.
    const option = b.option(bool, "raylib", "Link raylib to executable? Defaults to true") orelse true;
    const exe = b.addExecutable(.{
        .name = "game",
        .optimize = optimization,
        .target = target,
    });
    exe.linkLibC();
    exe.addCSourceFiles(.{ .files = &c_source_files, .flags = &c_flags, .language = .c });
    if (option) {
        const raylib = b.dependency("raylib", .{ .target = target, .optimize = optimization }).artifact("raylib");
        exe.linkLibrary(raylib);
    }
    return exe;
}

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});

    // Used to have different ways of compiling. But this one works fine, others were deleted
    const exe = buildWithLocalRaylib(b, optimize, target);
    b.installArtifact(exe);

    const run_artifact = b.addRunArtifact(exe);
    const run_step = b.step("run", "Builds and runs the executable");
    run_step.dependOn(&run_artifact.step);
}
