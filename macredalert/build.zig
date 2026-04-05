const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Configurable raylib paths (default: Homebrew on Apple Silicon)
    const raylib_include = b.option([]const u8, "raylib-include-path", "Path to raylib headers (default: /opt/homebrew/include)") orelse "/opt/homebrew/include";
    const raylib_lib = b.option([]const u8, "raylib-lib-path", "Path to raylib library (default: /opt/homebrew/lib)") orelse "/opt/homebrew/lib";

    // Create root module
    const root_module = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    root_module.linkSystemLibrary("c++", .{});

    // Link system-installed raylib
    root_module.addSystemIncludePath(.{ .cwd_relative = raylib_include });
    root_module.addLibraryPath(.{ .cwd_relative = raylib_lib });
    root_module.linkSystemLibrary("raylib", .{});

    // Link macOS frameworks required by raylib
    root_module.linkFramework("IOKit", .{});
    root_module.linkFramework("Cocoa", .{});
    root_module.linkFramework("OpenGL", .{});
    root_module.linkFramework("AudioToolbox", .{});
    root_module.linkFramework("CoreFoundation", .{});

    // Stub headers shadow Windows includes (highest priority)
    root_module.addSystemIncludePath(b.path("src/stubs"));

    // Compat headers (platform.h shim)
    root_module.addSystemIncludePath(b.path("src/compat"));

    // Original source include paths
    root_module.addIncludePath(.{ .cwd_relative = "../CODE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/INCLUDE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/DRAWBUFF" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/AUDIO" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/KEYBOARD" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/TIMER" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/PALETTE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/RAWFILE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/MISC" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/SHAPE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/IFF" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/FONT" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/MEM" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/WSA" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/TILE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/MONO" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/MOVIE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/PROFILE" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/DIPTHONG" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/WW_WIN" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/WINCOMM" });
    root_module.addIncludePath(.{ .cwd_relative = "../WIN32LIB/PLAYCD" });

    // Common C++ flags for legacy code
    const cxx_flags: []const []const u8 = &.{
        "-DWIN32",
        "-DENGLISH=1",
        "-std=c++14",
        "-Wno-register",
        "-Wno-writable-strings",
        "-Wno-reorder-ctor",
        "-Wno-dangling-else",
        "-Wno-parentheses",
        "-Wno-switch",
        "-Wno-unused-value",
        "-Wno-narrowing",
        "-Wno-return-type",
        "-Wno-c++11-compat-deprecated-writable-strings",
        "-Wno-logical-op-parentheses",
        "-Wno-tautological-compare",
        "-Wno-unused-variable",
        "-Wno-unused-but-set-variable",
        "-Wno-missing-braces",
        "-Wno-sign-compare",
        "-Wno-char-subscripts",
        "-Wno-sometimes-uninitialized",
        "-Wno-format",
        "-Wno-null-dereference",
        "-Wno-implicit-int-float-conversion",
        "-Wno-deprecated-declarations",
        "-Wno-pragma-pack",
        "-Wno-unknown-pragmas",
        "-Wno-ignored-pragmas",
        "-Wno-nonportable-include-path",
        "-Wno-extra-tokens",
        "-Wno-comment",
        "-Wno-undefined-bool-conversion",
        "-Wno-invalid-source-encoding",
        "-Wno-null-conversion",
        "-Wno-constant-conversion",
        "-Wno-empty-body",
        "-Wno-overloaded-virtual",
        "-Wno-address-of-temporary",
        "-Wno-extra-qualification",
        "-Wno-microsoft-extra-qualification",
        "-Wno-int-to-void-pointer-cast",
        "-Wno-void-pointer-to-int-cast",
        "-Wno-incompatible-pointer-types",
        "-Wno-int-conversion",
        "-Wno-implicit-function-declaration",
        "-Wno-bitfield-constant-conversion",
        "-Wno-pointer-to-int-cast",
        "-Wno-int-to-pointer-cast",
        "-DTRUE_FALSE_DEFINED",
        "-Wno-incompatible-library-redeclaration",
        "-Dfar=",
        "-Dcdecl=",
        "-D_far=",
        "-D__far=",
        "-fno-sanitize=undefined",
        "-fms-extensions",
        "-fpermissive",
        "-ferror-limit=50",
    };

    // CODE/ sources get FUNCTION.H force-included (monolithic include model)
    const code_cxx_flags: []const []const u8 = cxx_flags ++ &[_][]const u8{
        "-include", "fwd_types.h",
        "-include", "../CODE/FUNCTION.H",
    };

    // =========================================================================
    // Group 1: Original CODE/ sources (excluding platform-specific files)
    // =========================================================================
    root_module.addCSourceFiles(.{
        .root = .{ .cwd_relative = "../CODE" },
        .files = code_sources,
        .flags = code_cxx_flags,
    });

    // =========================================================================
    // Group 2: Original WIN32LIB/ sources (excluding files we replace)
    // =========================================================================
    root_module.addCSourceFiles(.{
        .root = .{ .cwd_relative = "../WIN32LIB" },
        .files = win32lib_sources,
        .flags = cxx_flags,
    });

    // =========================================================================
    // Group 3: Platform layer (Raylib-based replacements)
    // =========================================================================
    root_module.addCSourceFiles(.{
        .root = b.path("src/platform"),
        .files = &.{
            // Will be populated as we implement each phase
        },
        .flags = cxx_flags,
    });

    // =========================================================================
    // Group 4: Compat patches (patched original files + ASM replacements)
    // =========================================================================
    root_module.addCSourceFiles(.{
        .root = b.path("src/compat"),
        .files = &.{
            "asm_stubs.cpp",
        },
        .flags = cxx_flags,
    });

    // Create executable
    const exe = b.addExecutable(.{
        .name = "redalert",
        .root_module = root_module,
    });

    b.installArtifact(exe);

    // Run step: zig build run -- [args]
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run Red Alert");
    run_step.dependOn(&run_cmd.step);
}

// =============================================================================
// Source file lists
// =============================================================================

// CODE/ sources — all .CPP files EXCEPT platform-specific ones we replace
const code_sources: []const []const u8 = &.{
    "_WSPROTO.CPP",
    "2KEYFRAM.CPP",
    "AADATA.CPP",
    "ABSTRACT.CPP",
    "ADATA.CPP",
    "ADPCM.CPP",
    "AIRCRAFT.CPP",
    "ALLOC.CPP",
    "ANIM.CPP",
    "AUDIO.CPP",
    "B64PIPE.CPP",
    "B64STRAW.CPP",
    "BAR.CPP",
    "BASE.CPP",
    "BASE64.CPP",
    "BBDATA.CPP",
    "BDATA.CPP",
    "BENCH.CPP",
    "BFIOFILE.CPP",
    "BIGCHECK.CPP",
    "BLOWFISH.CPP",
    "BLOWPIPE.CPP",
    "BLWSTRAW.CPP",
    "BMP8.CPP",
    "BUFF.CPP",
    "BUILDING.CPP",
    "BULLET.CPP",
    "CARGO.CPP",
    "CARRY.CPP",
    "CCDDE.CPP",
    "CCFILE.CPP",
    "CCINI.CPP",
    "CCMPATH.CPP",
    "CCPTR.CPP",
    "CCTEN.CPP",
    "CDATA.CPP",
    "CDFILE.CPP",
    "CELL.CPP",
    "CHECKBOX.CPP",
    "CHEKLIST.CPP",
    "CLASS.CPP",
    "COLRLIST.CPP",
    "COMBAT.CPP",
    "COMBUF.CPP",
    // COMINIT.CPP -- excluded (COM init, Windows-only)
    "COMQUEUE.CPP",
    "CONFDLG.CPP",
    "CONNECT.CPP",
    "CONQUER.CPP",
    "CONST.CPP",
    "CONTROL.CPP",
    "COORD.CPP",
    "CRATE.CPP",
    "CRC.CPP",
    "CRCPIPE.CPP",
    "CRCSTRAW.CPP",
    "CREDITS.CPP",
    "CREW.CPP",
    "CSTRAW.CPP",
    // DDE.CPP -- excluded (Windows DDE)
    "DEBUG.CPP",
    "DESCDLG.CPP",
    "DIAL8.CPP",
    "DIALOG.CPP",
    "DIBFILE.CPP",
    "DIBUTIL.CPP",
    "DISPLAY.CPP",
    "DOOR.CPP",
    "DPMI.CPP",
    "DRIVE.CPP",
    "DROP.CPP",
    "DTABLE.CPP",
    "DYNAVEC.CPP",
    "EDIT.CPP",
    "EGOS.CPP",
    "ENDING.CPP",
    "EVENT.CPP",
    "EXPAND.CPP",
    "FACE.CPP",
    "FACING.CPP",
    "FACTORY.CPP",
    "FIELD.CPP",
    "FILE.CPP",
    "FINDPATH.CPP",
    "FIXED.CPP",
    "FLASHER.CPP",
    "FLY.CPP",
    "FOOT.CPP",
    "FUSE.CPP",
    "GADGET.CPP",
    "GAMEDLG.CPP",
    "GAUGE.CPP",
    "GETCPU.CPP",
    "GLOBALS.CPP",
    "GOPTIONS.CPP",
    "GSCREEN.CPP",
    "HDATA.CPP",
    "HEAP.CPP",
    "HELP.CPP",
    "HOUSE.CPP",
    "HSV.CPP",
    "ICONLIST.CPP",
    "IDATA.CPP",
    "INFANTRY.CPP",
    "INI.CPP",
    "INIBIN.CPP",
    "INICODE.CPP",
    "INIT.CPP",
    "INT.CPP",
    "INTERNET.CPP",
    "INTERPAL.CPP",
    "INTRO.CPP",
    "IOMAP.CPP",
    "IOOBJ.CPP",
    "IPX.CPP",
    "IPX95.CPP",
    "IPXADDR.CPP",
    "IPXCONN.CPP",
    "IPXGCONN.CPP",
    "IPXMGR.CPP",
    "ITABLE.CPP",
    "JSHELL.CPP",
    "KEY.CPP",
    "KEYBOARD.CPP",
    "KEYFRAME.CPP",
    "LAYER.CPP",
    "LCW.CPP",
    "LCWPIPE.CPP",
    "LCWSTRAW.CPP",
    "LCWUNCMP.CPP",
    "LINK.CPP",
    "LIST.CPP",
    "LOADDLG.CPP",
    "LOGIC.CPP",
    "LZO1X_C.CPP",
    "LZO1X_D.CPP",
    "LZOPIPE.CPP",
    "LZOSTRAW.CPP",
    "LZW.CPP",
    "LZWOTRAW.CPP",
    "LZWPIPE.CPP",
    "LZWSTRAW.CPP",
    "MAP.CPP",
    "MAPEDDLG.CPP",
    "MAPEDIT.CPP",
    "MAPEDPLC.CPP",
    "MAPEDSEL.CPP",
    "MAPEDTM.CPP",
    "MAPSEL.CPP",
    "MCI.CPP",
    // MCIMOVIE.CPP -- excluded (Windows MCI movie playback)
    "MENUS.CPP",
    "MISSION.CPP",
    "MIXFILE.CPP",
    "MONOC.CPP",
    "MOUSE.CPP",
    "MP.CPP",
    "MPGSET.CPP",
    "MPLAYER.CPP",
    // MPLIB.CPP -- excluded (modem)
    // MPLPC.CPP -- excluded (modem)
    "MPMGRD.CPP",
    "MPMGRW.CPP",
    "MPU.CPP",
    "MSGBOX.CPP",
    "MSGLIST.CPP",
    "NETDLG.CPP",
    "NOSEQCON.CPP",
    "NULLCONN.CPP",
    "NULLDLG.CPP",
    "NULLMGR.CPP",
    "NUMBER.CPP",
    "OBJECT.CPP",
    "ODATA.CPP",
    "OPTIONS.CPP",
    "OVERLAY.CPP",
    "PACKET.CPP",
    "PIPE.CPP",
    "PK.CPP",
    "PKPIPE.CPP",
    "PKSTRAW.CPP",
    "POWER.CPP",
    "PROFILE.CPP",
    "QUEUE.CPP",
    "RADAR.CPP",
    "RADIO.CPP",
    "RAMFILE.CPP",
    "RAND.CPP",
    "RANDOM.CPP",
    "RAWFILE.CPP", // Will be replaced by compat in Phase 2
    "RAWOLAPI.CPP",
    "READLINE.CPP",
    "RECT.CPP",
    "REINF.CPP",
    "RGB.CPP",
    "RNDSTRAW.CPP",
    "ROTBMP.CPP",
    "RULES.CPP",
    "SAVELOAD.CPP",
    "SCENARIO.CPP",
    "SCORE.CPP",
    "SCROLL.CPP",
    "SDATA.CPP",
    "SEDITDLG.CPP",
    "SENDFILE.CPP",
    "SEQCONN.CPP",
    "SESSION.CPP",
    "SHA.CPP",
    "SHAPEBTN.CPP",
    "SHAPIPE.CPP",
    "SHASTRAW.CPP",
    "SIDEBAR.CPP",
    "SLIDER.CPP",
    "SMUDGE.CPP",
    "SOUNDDLG.CPP",
    "SPECIAL.CPP",
    "SPRITE.CPP",
    "STARTUP.CPP", // Will be replaced by platform/entry_point.cpp in Phase 3
    "STATBTN.CPP",
    "STATS.CPP",
    "STRAW.CPP",
    "STUB.CPP",
    "SUPER.CPP",
    "SURFACE.CPP",
    "TAB.CPP",
    "TACTION.CPP",
    "TARCOM.CPP",
    "TARGET.CPP",
    "TCPIP.CPP",
    "TDATA.CPP",
    "TEAM.CPP",
    "TEAMTYPE.CPP",
    "TECHNO.CPP",
    "TEMP.CPP",
    "TEMPLATE.CPP",
    "TENMGR.CPP",
    "TERRAIN.CPP",
    "TEVENT.CPP",
    "TEXTBTN.CPP",
    "THEME.CPP",
    "TOGGLE.CPP",
    "TOOLTIP.CPP",
    "TRACKER.CPP",
    "TRIGGER.CPP",
    "TRIGTYPE.CPP",
    "TURRET.CPP",
    "TXTLABEL.CPP",
    "UDATA.CPP",
    "UDPADDR.CPP",
    "UNIT.CPP",
    "UTRACKER.CPP",
    "VDATA.CPP",
    "VECTOR.CPP",
    "VERSION.CPP",
    "VESSEL.CPP",
    "VISUDLG.CPP",
    "VORTEX.CPP",
    "W95TRACE.CPP",
    "WARHEAD.CPP",
    "WEAPON.CPP",
    "WINSTUB.CPP", // Will be replaced by platform layer in Phase 3
    // WOL_CGAM.CPP -- excluded (Westwood Online)
    // WOL_CHAT.CPP -- excluded
    // WOL_DNLD.CPP -- excluded
    // WOL_GSUP.CPP -- excluded
    // WOL_LOGN.CPP -- excluded
    // WOL_MAIN.CPP -- excluded
    // WOL_OPT.CPP -- excluded
    // WOLAPIOB.CPP -- excluded
    "WOLEDIT.CPP",
    // WOLSTRNG.CPP -- excluded
    "WRITEPCX.CPP",
    "WSPIPX.CPP",
    "WSPROTO.CPP",
    "WSPUDP.CPP",
    "XPIPE.CPP",
    "XSTRAW.CPP",
};

// WIN32LIB/ sources — excluding SRCDEBUG/, OLD/, TEST/, EXAMPLE/, and files we replace
const win32lib_sources: []const []const u8 = &.{
    // AUDIO (SOUNDIO.CPP will be replaced by platform layer in Phase 5)
    "AUDIO/SOUNDINT.CPP",
    "AUDIO/SOUNDIO.CPP",
    "AUDIO/SOUNDLCK.CPP",
    // DIPTHONG
    "DIPTHONG/_DIPTABL.CPP",
    "DIPTHONG/DIPTHONG.CPP",
    // DRAWBUFF
    "DRAWBUFF/BUFFER.CPP",
    "DRAWBUFF/BUFFGLBL.CPP",
    "DRAWBUFF/DRAWRECT.CPP",
    "DRAWBUFF/GBUFFER.CPP",
    "DRAWBUFF/ICONCACH.CPP",
    "DRAWBUFF/REGIONSZ.CPP",
    // FONT
    "FONT/FONT.CPP",
    "FONT/LOADFONT.CPP",
    "FONT/SET_FONT.CPP",
    // IFF
    "IFF/IFF.CPP",
    "IFF/LOAD.CPP",
    "IFF/LOADPCX.CPP",
    "IFF/LOADPICT.CPP",
    "IFF/WRITELBM.CPP",
    "IFF/WRITEPCX.CPP",
    // KEYBOARD
    "KEYBOARD/KEYBOARD.CPP",
    "KEYBOARD/MOUSE.CPP",
    // MEM
    "MEM/ALLOC.CPP",
    "MEM/MEM.CPP",
    "MEM/NEWDEL.CPP",
    // MISC (DDRAW.CPP will be replaced by platform layer in Phase 3)
    "MISC/DDRAW.CPP",
    "MISC/DELAY.CPP",
    "MISC/EXIT.CPP",
    "MISC/FINDARGV.CPP",
    "MISC/IRANDOM.CPP",
    "MISC/LIB.CPP",
    "MISC/VERSION.CPP",
    // MONO
    "MONO/MONO.CPP",
    // MOVIE
    "MOVIE/MOVIE.CPP",
    // PALETTE
    "PALETTE/LOADPAL.CPP",
    "PALETTE/MORPHPAL.CPP",
    "PALETTE/PALETTE.CPP",
    // PLAYCD
    "PLAYCD/GETCD.CPP",
    "PLAYCD/REDBOOK.CPP",
    // PROFILE
    "PROFILE/PROFILE.CPP",
    "PROFILE/WPROFILE.CPP",
    // RAWFILE
    "RAWFILE/CCFILE.CPP",
    "RAWFILE/RAWFILE.CPP",
    // SHAPE
    "SHAPE/GETSHAPE.CPP",
    "SHAPE/PRIOINIT.CPP",
    // TILE
    "TILE/ICONSET.CPP",
    // TIMER (TIMER.CPP will be replaced in Phase 6)
    "TIMER/TIMER.CPP",
    "TIMER/TIMERDWN.CPP",
    "TIMER/TIMERINI.CPP",
    // WINCOMM
    "WINCOMM/MODEMREG.CPP",
    "WINCOMM/WINCOMM.CPP",
    // WSA
    "WSA/WSA.CPP",
    // WW_WIN
    "WW_WIN/WINDOWS.CPP",
    "WW_WIN/WINHIDE.CPP",
};
