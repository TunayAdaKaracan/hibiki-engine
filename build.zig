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

var cdb_targets: [1]*std.Build.Step.Compile = undefined;

pub fn build(b: *std.Build) void {
    const optimization = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});

    // The reason raylib is an option:
    // I am still creating many aspects of the engine. Starting with simple stuff like arrays
    // and actual structures containing level data and beatmap data. Up until everything can be parsed, raylib will not be used.
    // Hence no need to actually compile and link raylib. This will be removed once engine is ready to work with a graphics library.
    const link_raylib = b.option(bool, "raylib", "Link raylib to the executable? Defaults to truee") orelse true;
    const cdb = b.option(bool, "cdb", "Compile compile_commands.zig") orelse false;
    const exe = b.addExecutable(.{
        .name = "game",
        .optimize = optimization,
        .target = target,
    });

    exe.linkLibC();
    exe.addIncludePath(b.path("include/"));
    exe.addCSourceFiles(.{ .files = &c_source_files, .flags = &c_flags, .language = .c });

    if (link_raylib) {
        const raylib_dep = if (cdb) b.dependency("raylib", .{
            .target = target,
            .optimize = optimization,
            .linux_display_backend = .X11,
        }) else b.dependency("raylib", .{
            .target = target,
            .optimize = optimization,
        });
        exe.linkLibrary(raylib_dep.artifact("raylib"));
    }

    if (cdb) {
        cdb_targets[0] = exe;
        b.getInstallStep().dependOn(zcc.createStep(b, "cdb", &cdb_targets));
    } else {
        b.installArtifact(exe);

        const run_artifact = b.addRunArtifact(exe);
        const run_step = b.step("run", "Builds and runs the executable");
        run_step.dependOn(&run_artifact.step);
    }
}
