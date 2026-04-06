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
        "-Wno-builtin-requires-header",
        "-Wno-bool-operation",
        "-Wno-deprecated-increment-bool",
        "-Wno-enum-compare",
        "-Wno-string-plus-int",
        "-Wno-null-arithmetic",
        "-Wno-c++17-compat",
        "-Wno-bool-conversion",
        "-Wno-delete-incomplete",
        "-Wno-sizeof-pointer-div",
        "-Wno-nonnull",
        "-Wno-writable-strings",
        "-Wno-deprecated-builtins",
        "-Wno-shadow",
        "-Wno-shadow-all",
        "-Wno-varargs",
        "-Dfar=",
        "-Dcdecl=",
        "-D_far=",
        "-D__far=",
        "-Dindex(s,c)=strchr(s,c)",
        "-fno-sanitize=undefined",
        "-fms-extensions",
        "-fdelayed-template-parsing",
        "-fpermissive",
        "-ferror-limit=50",
    };

    // CODE/ sources get FUNCTION.H force-included (monolithic include model)
    const code_cxx_flags: []const []const u8 = cxx_flags ++ &[_][]const u8{
        "-include", "/Users/tgomareli/Development/redalert/CnC_Red_Alert/macredalert/src/compat/fwd_types.h",
        "-include", "/Users/tgomareli/Development/redalert/CnC_Red_Alert/macredalert/src/compat/FUNCTION.H",
    };

    // =========================================================================
    // Group 1: Original CODE/ sources (excluding platform-specific files)
    // =========================================================================
    root_module.addCSourceFiles(.{
        .root = .{ .cwd_relative = "../CODE" },
        .files = code_sources,
        .flags = code_cxx_flags,
    });

    // WIN32LIB sources — fwd_types.h comes via windows.h stub, no FUNCTION.H
    const win32lib_cxx_flags: []const []const u8 = cxx_flags;

    // =========================================================================
    // Group 2: Original WIN32LIB/ sources (excluding files we replace)
    // =========================================================================
    root_module.addCSourceFiles(.{
        .root = .{ .cwd_relative = "../WIN32LIB" },
        .files = win32lib_sources,
        .flags = win32lib_cxx_flags,
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

    // Linker stubs need FUNCTION.H (they reference game types)
    root_module.addCSourceFiles(.{
        .root = b.path("src/compat"),
        .files = &.{
            "linker_stubs.cpp",
            "template_inst.cpp",
        },
        .flags = code_cxx_flags,
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
    // "_WSPROTO.CPP", -- excluded (non-essential),
    // "2KEYFRAM.CPP", -- duplicates KEYFRAME.CPP
    "AADATA.CPP",
    "ABSTRACT.CPP",
    "ADATA.CPP",
    "ADPCM.CPP",
    "AIRCRAFT.CPP",
    "ALLOC.CPP",
    "ANIM.CPP",
    // "AUDIO.CPP", -- excluded
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
    // "BMP8.CPP", -- excluded (non-essential),
    "BUFF.CPP",
    "BUILDING.CPP",
    "BULLET.CPP",
    "CARGO.CPP",
    "CARRY.CPP",
    "CCDDE.CPP",
    "CCFILE.CPP",
    "CCINI.CPP",
    // "CCMPATH.CPP", -- excluded (non-essential),
    "CCPTR.CPP",
    // "CCTEN.CPP", -- excluded (non-essential),
    "CDATA.CPP",
    "CDFILE.CPP",
    "CELL.CPP",
    "CHECKBOX.CPP",
    "CHEKLIST.CPP",
    "CLASS.CPP",
    "COLRLIST.CPP",
    "COMBAT.CPP",
    // "COMBUF.CPP", -- excluded
    // COMINIT.CPP -- excluded (COM init, Windows-only)
    // "COMQUEUE.CPP", -- excluded (non-essential),
    "CONFDLG.CPP",
    // "CONNECT.CPP", -- excluded
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
    // "DIBFILE.CPP", -- excluded (non-essential),
    // "DIBUTIL.CPP", -- excluded (non-essential),
    "DISPLAY.CPP",
    "DOOR.CPP",
    // "DPMI.CPP", -- excluded
    "DRIVE.CPP",
    "DROP.CPP",
    // "DTABLE.CPP", -- duplicates ADPCM tables
    "DYNAVEC.CPP",
    "EDIT.CPP",
    "EGOS.CPP",
    "ENDING.CPP",
    "EVENT.CPP",
    "EXPAND.CPP",
    "FACE.CPP",
    "FACING.CPP",
    "FACTORY.CPP",
    // "FIELD.CPP", -- excluded
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
    // "GETCPU.CPP", -- excluded
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
    // "INTERNET.CPP", -- excluded
    "INTERPAL.CPP",
    "INTRO.CPP",
    "IOMAP.CPP",
    "IOOBJ.CPP",
    // "IPX.CPP", -- excluded (non-essential),
    // "IPX95.CPP", -- excluded (non-essential),
    // "IPXADDR.CPP", -- excluded (non-essential),
    // "IPXCONN.CPP", -- excluded (non-essential),
    // "IPXGCONN.CPP", -- excluded (non-essential),
    // "IPXMGR.CPP", -- excluded (non-essential),
    // "ITABLE.CPP", -- duplicates tables
    "JSHELL.CPP",
    // "KEY.CPP", -- duplicates KEYBOARD.CPP
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
    // "LZWOTRAW.CPP", -- duplicates LZWSTRAW
    "LZWPIPE.CPP",
    "LZWSTRAW.CPP",
    "MAP.CPP",
    "MAPEDDLG.CPP",
    "MAPEDIT.CPP",
    "MAPEDPLC.CPP",
    "MAPEDSEL.CPP",
    "MAPEDTM.CPP",
    // "MAPSEL.CPP", -- excluded
    // "MCI.CPP", -- excluded
    // MCIMOVIE.CPP -- excluded (Windows MCI movie playback)
    "MENUS.CPP",
    "MISSION.CPP",
    "MIXFILE.CPP",
    "MONOC.CPP",
    "MOUSE.CPP",
    // "MP.CPP", -- excluded
    // "MPGSET.CPP", -- excluded
    // "MPLAYER.CPP", -- excluded
    // MPLIB.CPP -- excluded (modem)
    // MPLPC.CPP -- excluded (modem)
    // "MPMGRD.CPP", -- excluded (non-essential),
    // "MPMGRW.CPP", -- excluded (non-essential),
    // "MPU.CPP", -- excluded
    "MSGBOX.CPP",
    "MSGLIST.CPP",
    // "NETDLG.CPP", -- excluded
    // "NOSEQCON.CPP", -- excluded (non-essential),
    // "NULLCONN.CPP", -- excluded (non-essential),
    // "NULLDLG.CPP", -- excluded (non-essential),
    // "NULLMGR.CPP", -- excluded (non-essential),
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
    // "RAWOLAPI.CPP", -- excluded (non-essential),
    "READLINE.CPP",
    "RECT.CPP",
    "REINF.CPP",
    "RGB.CPP",
    "RNDSTRAW.CPP",
    "ROTBMP.CPP",
    "RULES.CPP",
    "SAVELOAD.CPP",
    "SCENARIO.CPP",
    // "SCORE.CPP", -- excluded
    "SCROLL.CPP",
    "SDATA.CPP",
    "SEDITDLG.CPP",
    // "SENDFILE.CPP", -- excluded
    // "SEQCONN.CPP", -- excluded
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
    // "STATS.CPP", -- excluded (non-essential),
    "STRAW.CPP",
    // "STUB.CPP", -- excluded
    "SUPER.CPP",
    "SURFACE.CPP",
    "TAB.CPP",
    "TACTION.CPP",
    // "TARCOM.CPP", -- excluded (dead code; TarComClass::AI accesses UnitClass members not in hierarchy)
    "TARGET.CPP",
    // "TCPIP.CPP", -- excluded (non-essential),
    "TDATA.CPP",
    "TEAM.CPP",
    "TEAMTYPE.CPP",
    "TECHNO.CPP",
    // TEMP.CPP -- excluded (patch notes file, not compilable source)
    "TEMPLATE.CPP",
    // "TENMGR.CPP", -- excluded (non-essential),
    "TERRAIN.CPP",
    "TEVENT.CPP",
    "TEXTBTN.CPP",
    "THEME.CPP",
    "TOGGLE.CPP",
    // "TOOLTIP.CPP", -- excluded (non-essential),
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
    // "WINSTUB.CPP", -- excluded // Will be replaced by platform layer in Phase 3
    // WOL_CGAM.CPP -- excluded (Westwood Online)
    // WOL_CHAT.CPP -- excluded
    // WOL_DNLD.CPP -- excluded
    // WOL_GSUP.CPP -- excluded
    // WOL_LOGN.CPP -- excluded
    // WOL_MAIN.CPP -- excluded
    // WOL_OPT.CPP -- excluded
    // WOLAPIOB.CPP -- excluded
    // "WOLEDIT.CPP", -- excluded (non-essential),
    // WOLSTRNG.CPP -- excluded
    // "WRITEPCX.CPP", -- excluded
    // "WSPIPX.CPP", -- excluded (non-essential),
    // "WSPROTO.CPP", -- excluded (non-essential),
    // "WSPUDP.CPP", -- excluded (non-essential),
    "XPIPE.CPP",
    "XSTRAW.CPP",
};

// WIN32LIB/ sources — excluding SRCDEBUG/, OLD/, TEST/, EXAMPLE/, and files we replace
const win32lib_sources: []const []const u8 = &.{
    // AUDIO (will be replaced by Raylib audio in Phase 5)
    // "AUDIO/SOUNDINT.CPP",
    // "AUDIO/SOUNDIO.CPP",
    // "AUDIO/SOUNDLCK.CPP",
    // DIPTHONG
    "DIPTHONG/_DIPTABL.CPP",
    "DIPTHONG/DIPTHONG.CPP",
    // DRAWBUFF
    "DRAWBUFF/BUFFER.CPP",
    "DRAWBUFF/BUFFGLBL.CPP",
    "DRAWBUFF/DRAWRECT.CPP",
    "DRAWBUFF/GBUFFER.CPP",
    // "DRAWBUFF/ICONCACH.CPP", -- includes game headers that need FUNCTION.H
    "DRAWBUFF/REGIONSZ.CPP",
    // FONT
    "FONT/FONT.CPP",
    "FONT/LOADFONT.CPP",
    "FONT/SET_FONT.CPP",
    // IFF
    "IFF/IFF.CPP",
    "IFF/LOAD.CPP",
    // "IFF/LOADPCX.CPP", -- includes function.h, needs CODE/ treatment
    // "IFF/LOADPICT.CPP", -- duplicated
    "IFF/WRITELBM.CPP",
    // "IFF/WRITEPCX.CPP", -- duplicated in CODE/
    // KEYBOARD (will be replaced by Raylib input in Phase 4)
    // "KEYBOARD/KEYBOARD.CPP",
    // "KEYBOARD/MOUSE.CPP",
    // MEM
    // "MEM/ALLOC.CPP", -- duplicated by CODE/ALLOC.CPP
    // "MEM/MEM.CPP", -- duplicated
    // "MEM/NEWDEL.CPP", -- duplicated
    // MISC (DDRAW.CPP will be replaced by Raylib video in Phase 3)
    // "MISC/DDRAW.CPP",
    "MISC/DELAY.CPP",
    "MISC/EXIT.CPP",
    "MISC/FINDARGV.CPP",
    "MISC/IRANDOM.CPP",
    "MISC/LIB.CPP",
    "MISC/VERSION.CPP",
    // MONO (debug display not needed)
    // "MONO/MONO.CPP",
    // MOVIE (MCI not available, replaced later)
    // "MOVIE/MOVIE.CPP",
    // PALETTE
    "PALETTE/LOADPAL.CPP",
    "PALETTE/MORPHPAL.CPP",
    "PALETTE/PALETTE.CPP",
    // PLAYCD (CD audio not needed on macOS)
    // "PLAYCD/GETCD.CPP",
    // "PLAYCD/REDBOOK.CPP",
    // PROFILE (both files have issues - will address in later phase)
    // "PROFILE/PROFILE.CPP",
    // "PROFILE/WPROFILE.CPP",
    // RAWFILE (CCFILE duplicated in CODE/, RAWFILE will be replaced in Phase 2)
    // "RAWFILE/CCFILE.CPP",
    // "RAWFILE/RAWFILE.CPP",
    // SHAPE
    "SHAPE/GETSHAPE.CPP",
    "SHAPE/PRIOINIT.CPP",
    // TILE
    "TILE/ICONSET.CPP",
    // TIMER (will be replaced in Phase 6)
    // "TIMER/TIMER.CPP",
    // "TIMER/TIMERDWN.CPP",
    // "TIMER/TIMERINI.CPP",
    // WINCOMM (serial modem not needed)
    // "WINCOMM/MODEMREG.CPP",
    // "WINCOMM/WINCOMM.CPP",
    // WSA
    "WSA/WSA.CPP",
    // WW_WIN
    "WW_WIN/WINDOWS.CPP",
    "WW_WIN/WINHIDE.CPP",
};
