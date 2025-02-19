% xmobar - A Minimalistic Text Based Status Bar

About
=====

xmobar is a minimalistic, text based, status bar. It was originally
designed and implemented by Andrea Rossato to work with [xmonad],
but it's actually usable with any window-manager.

xmobar was inspired by the [Ion3] status bar, and supports similar
features, like dynamic color management, output templates, and
extensibility through plugins.

This page documents xmobar 0.15 (see [release notes]).

[This screenshot] shows xmobar running under [sawfish], with
antialiased fonts. And [this one] is my desktop with [xmonad] and two
instances of xmobar.

[release notes]: http://projects.haskell.org/xmobar/releases.html
[xmonad]: http://xmonad.org
[Ion3]: http://tuomov.iki.fi/software/
[This screenshot]: http://projects.haskell.org/xmobar/xmobar-sawfish.png
[this one]: http://projects.haskell.org/xmobar/xmobar-xmonad.png

Bug Reports
===========

To submit bug reports you can use the [bug tracker over at Google
code] or send mail to our [Mailing list].

[bug tracker over at Google code]: http://code.google.com/p/xmobar/issues

Installation
============

## Using cabal-install

Xmobar is available from [Hackage], and you can install it using
`cabal-install`:

        cabal install xmobar

See below for a list of optional compilation flags that will enable
some optional plugins. For instance, to install xmobar with all the
bells and whistles, use:

        cabal install xmobar --flags="all_extensions"

## From source

If you don't have `cabal-install` installed, you can get xmobar's
source code in a variety of ways:

  - From [Hackage]. Just download [xmobar-0.15.tar.gz] from xmobar's
    hackage page.
  - From [Github]. You can also obtain a tarball in [Github's
    downloads page]. You'll find there links to each tagged release.
  - From the bleeding edge repo. If you prefer to live dangerously,
    just get the latest and greatest (and buggiest, i guess) using
    git:
        git clone git://github.com/jaor/xmobar

[xmobar-0.15.tar.gz]: http://hackage.haskell.org/packages/archive/xmobar/0.15/xmobar-0.15.tar.gz
[Github's downloads page]: https://github.com/jaor/xmobar/downloads

To install simply run (if needed):

        tar xvfz xmobar-0.15
        cd xmobar-0.15

If you have cabal installed, you can now use it from within xmobar's
source tree. Otherwise, run the configure script:

        runhaskell Setup.lhs configure

        # To enable UTF-8 support run:
        runhaskell Setup.lhs configure --flags="with_utf8"

        # To enable both XFT and UTF-8 support run:
        runhaskell Setup.lhs configure --flags="with_xft"

        # To enable all extensions
        runhaskell Setup.lhs configure --flags="all_extensions"

Now you can build the source:

        runhaskell Setup.lhs build
        runhaskell Setup.lhs install # possibly to be run as root


## Optional features

You can configure xmobar to include some optional plugins and
features, which are not compiled by default. To that end, you need to
add one or more flags to either the cabal install command or the
configure setup step, as shown in the examples above.

Extensions need additional libraries (listed below) that will be
automatically downloaded and installed if you're using cabal install.
Otherwise, you'll need to install them yourself.

`with_threaded`
:    Uses GHC's threaded runtime.  Use this option if xmobar enters a
     high-CPU regime right after starting.

`with_utf8`
:    UTF-8 support. Requires the [utf8-string] package.

`with_xft`
:    Antialiased fonts. Requires the [X11-xft] package. This option
     automatically enables UTF-8.

     To use XFT fonts you need to use the `xft:` prefix in the `font`
     configuration option. For instance:

        font = "xft:Times New Roman-10:italic"

`with_mpd`
:    Enables support for the [MPD] daemon. Requires the [libmpd] package.

`with_mpris`
:    Enables support for MPRIS v1/v2 protocol.
     Requires the [dbus-core] and [text] packages.

`with_inotify`
:    Support for inotify in modern linux kernels. This option is needed
     for the MBox and Mail plugins to work. Requires the [hinotify]
     package.

`with_iwlib`
:    Support for wireless cards. Enables the Wireless plugin. No Haskell
     library is required, but you will need the [iwlib] C library and
     headers in your system (e.g., install `libiw-dev` in Debian-based
     systems).

`with_alsa`
:    Support for ALSA sound cards. Enables the Volume plugin. Requires the
     [alsa-mixer] package.

`with_datezone`
:    Support for other timezones. Enables the DateZone plugin.
     Requires [timezone-olson] and [timezone-series] package.

`all_extensions`
:    Enables all the extensions above.

Running xmobar
==============

You can now run xmobar with:

        xmobar /path/to/config &

or

        xmobar &

if you have the default configuration file saved as `~/.xmobarrc`

### Signal Handling

Since 0.14 xmobar reacts to SIGUSR1 and SIGUSR2:

- After receiving SIGUSR1 xmobar moves its position to the next screen.

- After receiving SIGUSR2 xmobar repositions it self on the current screen.

Configuration
=============

## Quick Start

See [samples/xmobar.config] for an example.

[samples/xmobar.config]: http://github.com/jaor/xmobar/raw/master/samples/xmobar.config

For the output template:

- `%command%` will execute command and print the output. The output
  may contain markups to change the characters' color.

- `<fc=#FF0000>string</fc>` will print `string` with `#FF0000` color
  (red).

Other configuration options:

`font`
:    Name of the font to be used. Use the `xft:` prefix for XFT fonts.

`bgColor`
:    Background color.

`fgColor`
:    Default font color.

`position`
:     Top, TopW, TopSize, Bottom, BottomW, BottomSize or Static (with x, y,
      width and height).

:     TopW and BottomW take 2 arguments: an alignment parameter (L for
      left, C for centered, R for Right) and an integer for the
      percentage width xmobar window will have in respect to the
      screen width.

:     TopSize and BottomSize take 3 arguments: an alignment parameter, an
      integer for the percentage width, and an integer for the minimum pixel
      height that the xmobar window will have.

:     For example:

:          position = BottomW C 75

:     to place xmobar at the bottom, centered with the 75% of the screen width.

:     Or

:          position = Static { xpos = 0 , ypos = 0, width = 1024, height = 15 }

:     or

:         position = Top

`border`
:     TopB, TopBM, BottomB, BottomBM, FullB, FullBM or NoBorder (default).

:     TopB, BottomB, FullB take no arguments, and request drawing a
      border at the top, bottom or around xmobar's window,
      respectively.

:     TopBM, BottomBM, FullBM take an integer argument, which is the
      margin, in pixels, between the border of the window and the
      drawn border.

`borderColor`
:     Border color.

`commands`
:    For setting the options of the programs to run (optional).

`sepChar`
:    The character to be used for indicating commands in the output
     template (default '%').

`alignSep`
:    a 2 character string for aligning text in the output template. The
     text before the first character will be align to left, the text in
     between the 2 characters will be centered, and the text after the
     second character will be align to the right.

`template`
:    The output template.

### Running xmobar with i3status

xmobar can be used to display information generated by [i3status], a
small program that gathers system information and outputs it in
formats suitable for being displayed by the dzen2 status bar, wmii's
status bar or xmobar's `StdinReader`.  See [i3status manual] for
further details.

## Command Line Options

xmobar can be either configured with a configuration file or with
command line options. In the second case, the command line options
will overwrite the corresponding options set in the configuration
file.

Example:

    xmobar -B white -a right -F blue -t '%LIPB%' -c '[Run Weather "LIPB" [] 36000]'

This is the list of command line options (the output of
xmobar --help):

    Usage: xmobar [OPTION...] [FILE]
    Options:
      -h, -?        --help                 This help
      -V            --version              Show version information
      -f font name  --font=font name       The font name
      -B bg color   --bgcolor=bg color     The background color. Default black
      -F fg color   --fgcolor=fg color     The foreground color. Default grey
      -o            --top                  Place xmobar at the top of the screen
      -b            --bottom               Place xmobar at the bottom of the screen
      -a alignsep   --alignsep=alignsep    Separators for left, center and right text
                                           alignment. Default: '}{'
      -s char       --sepchar=char         The character used to separate commands in
                                           the output template. Default '%'
      -t template   --template=template    The output template
      -c commands   --commands=commands    The list of commands to be executed
      -C command    --add-command=command  Add to the list of commands to be executed
      -x screen     --screen=screen        On which X screen number to start

    Mail bug reports and suggestions to <xmobar@projects.haskell.org>

## The Output Template

The output template must contain at least one command. xmobar will
parse the template and will search for the command to be executed in
the `commands` configuration option. First an `alias` will be searched
(plugins such as Weather or Network have default aliases, see below).
After that, the command name will be tried. If a command is found, the
arguments specified in the `commands` list will be used.

If no command is found in the `commands` list, xmobar will ask the
operating system to execute a program with the name found in the
template. If the execution is not successful an error will be
reported.

## The `commands` Configuration Option

The `commands` configuration option is a list of commands information
and arguments to be used by xmobar when parsing the output template.
Each member of the list consists in a command prefixed by the `Run`
keyword. Each command has arguments to control the way xmobar is going
to execute it.

The option consists in a list of commands separated by a comma and
enclosed by square parenthesis.

Example:

    [Run Memory ["-t","Mem: <usedratio>%"] 10, Run Swap [] 10]

to run the Memory monitor plugin with the specified template, and the
swap monitor plugin, with default options, every second.

The only internal available command is `Com` (see below Executing
External Commands). All other commands are provided by plugins. xmobar
comes with some plugins, providing a set of system monitors, a
standard input reader, an Unix named pipe reader, a configurable date
plugin, and much more: we list all available plugins below.

To remove them see below Installing/Removing a Plugin

Other commands can be created as plugins with the Plugin
infrastructure. See below Writing a Plugin

## System Monitor Plugins

This is the description of the system monitor plugins that are
installed by default.

Each monitor has an `alias` to be used in the output template.
Monitors have default aliases.

### `Uptime Args RefreshRate`

- Aliases to `uptime`
- Args: default monitor arguments (see below). The low and high
  thresholds refer to the number of days.
- Variables that can be used with the `-t`/`--template` argument:
  `days`, `hours`, `minutes`, `seconds`. The total uptime is the
  sum of all those fields. You can set the `-S` argument to "True"
  to add units to the display of those numeric fields.
- Default template: `Up: <days>d <hours>h <minutes>m`

### `Weather StationID Args RefreshRate`

- Aliases to the Station ID: so `Weather "LIPB" []` can be used in template as `%LIPB%`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `station`, `stationState`, `year`, `month`, `day`, `hour`,
	    `wind`, `visibility`, `skyCondition`, `tempC`, `tempF`,
	    `dewPoint`, `rh`, `pressure`
- Default template: `<station>: <tempC>C, rh <rh>% (<hour>)`
- Requires `curl` in the `$PATH` to retrieve weather information from
  `http://weather.noaa.gov`

### `Network Interface Args RefreshRate`

- Aliases to the interface name: so `Network "eth0" []` can be used as
  `%eth0%`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
  `dev`, `rx`, `tx`, `rxbar`, `txbar`. Reception and transmission
  rates (`rx` and `tx`) are displayed in Kbytes per second, and you
  can set the `-S` to "True" to make them displayed with units (the
  string "Kb/s").
- Default template: `<dev>: <rx>KB|<tx>KB`

### `Wireless Interface Args RefreshRate`

- Aliases to the interface name with the suffix "wi": thus, `Wirelss
  "wlan0" []` can be used as `%wlan0wi%`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
            `essid`, `quality`, `qualitybar`
- Default template: `<essid> <quality>`
- Requires the C library [iwlib] (part of the wireless tools suite)
  installed in your system. In addition, to activate this plugin you
  must pass `--flags="with_iwlib"` during compilation.

### `Memory Args RefreshRate`

- Aliases to `memory`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
             `total`, `free`, `buffer`, `cache`, `rest`, `used`,
             `usedratio`, `usedbar`, `freebar`
- Default template: `Mem: <usedratio>% (<cache>M)`

### `Swap Args RefreshRate`

- Aliases to `swap`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `total`, `used`, `free`, `usedratio`
- Default template: `Swap: <usedratio>%`

### `Cpu Args RefreshRate`

- Aliases to `cpu`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `total`, `bar`, `user`, `nice`, `system`, `idle`, `iowait`
- Default template: `Cpu: <total>%`

### `MultiCpu Args RefreshRate`

- Aliases to `multicpu`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `autototal`, `autobar`, `autouser`, `autonice`,
	    `autosystem`, `autoidle`, `total`, `bar`, `user`, `nice`,
	    `system`, `idle`, `total0`, `bar0`, `user0`, `nice0`,
	    `system0`, `idle0`, ...
  The auto* variables automatically detect the number of CPUs on the system
  and display one entry for each.
- Default template: `Cpu: <total>%`

### `Battery Args RefreshRate`

- Same as `BatteryP ["BAT0", "BAT1", "BAT2"] Args RefreshRate`.

### `BatteryP Dirs Args RefreshRate`

- Aliases to `battery`
- Dirs: list of directories in `/sys/class/power_supply/` where to
  look for the ACPI files of each battery. Example:
  `["BAT0","BAT1","BAT2"]`. Only the first 3 directories will be
  searched.
- Args: default monitor arguments (see below), plus the following specif ones:
    - `-O`: string for AC "on" status (default: "On")
    - `-o`: string for AC "off" status (default: "Off")
    - `-L`: low power (`watts`) threshold (default: -12)
    - `-H`: high power threshold (default: -10)
    - `-l`: color to display power lower than the `-L` threshold
    - `-m`: color to display power lower than the `-H` threshold
    - `-h`: color to display power highter than the `-H` threshold
    - `-p`: color to display positive power (battery charging)
    - `-f`: file in `/sys/class/power_supply` with AC info (default:
      "AC/online")

- Variables that can be used with the `-t`/`--template` argument:
	    `left`, `leftbar`, `timeleft`, `watts`, `acstatus`
- Default template: `Batt: <watts>, <left>% / <timeleft>`
- Example (note that you need "--" to separate regular monitor options from
  Battery's specific ones):

         Run BatteryP ["BAT0"]
                      ["-t", "<acstatus><watts> (<left>%)",
                       "-L", "10", "-H", "80", "-p", "3",
                       "--", "-O", "<fc=green>On</fc> - ", "-o", "",
                       "-L", "-15", "-H", "-5",
                       "-l", "red", "-m", "blue", "-h", "green"]
                      600
  In the above example, the thresholds before the "--" separator
  refer to the `<left>` field, while those after the separator affect
  how `<watts>` is displayed.

### `TopProc Args RefreshRate`

- Aliases to `top`
- Args: default monitor arguments (see below). The low and high
  thresholds (`-L` and `-H`) denote, for memory entries, the percent
  of the process memory over the total amount of memory currently in
  use and, for cpu entries, the activity percentage (i.e., the value
  of `cpuN`, which takes values between 0 and 100).
- Variables that can be used with the `-t`/`--template` argument:
	    `no`, `name1`, `cpu1`, `both1`, `mname1`, `mem1`, `mboth1`,
            `name2`, `cpu2`, `both2`, `mname2`, `mem2`, `mboth2`, ...
- Default template: `<both1>`
- Displays the name and cpu/mem usage of running processes (`bothn`
  and `mboth` display both, and is useful to specify an overall
  maximum and/or minimum width, using the `-m`/`-M` arguments. `no` gives
  the total number of processes.

### `TopMem Args RefreshRate`

- Aliases to `topmem`
- Args: default monitor arguments (see below). The low and high
  thresholds (`-L` and `-H`) denote the percent of the process memory
  over the total amount of memory currently in use.
- Variables that can be used with the `-t`/`--template` argument:
	    `name1`, `mem1`, `both1`, `name2`, `mem2`, `both2`, ...
- Default template: `<both1>`
- Displays the name and RSS (resident memory size) of running
  processes (`bothn` displays both, and is useful to specify an
  overall maximum and/or minimum width, using the `-m`/`-M` arguments.

### `DiskU Disks Args RefreshRate`

- Aliases to `disku`
- Disks: list of pairs of the form (device or mount point, template),
  where the template can contain <size>, <free>, <used>, <freep> or
  <usedp>, <freebar> or <usedbar> for total, free, used, free
  percentage and used percentage of the given file system capacity.
- Args: default monitor arguments (see below). `-t`/`--template` is ignored.
- Default template: none (you must specify a template for each file system).
- Example:

         DiskU [("/", "<used>/<size>"), ("sdb1", "<usedbar>")]
               ["-L", "20", "-H", "50", "-m", "1", "-p", "3",]
               20

### `DiskIO Disks Args RefreshRate`

- Aliases to `diskio`
- Disks: list of pairs of the form (device or mount point, template),
  where the template can contain <total>, <read>, <write> for total,
  read and write speed, respectively.
- Args: default monitor arguments (see below). `-t`/`--template` is ignored.
- Default template: none (you must specify a template for each file system).
- Example:

         Disks [("/", "<read> <write>"), ("sdb1", "<total>")] [] 10

### `ThermalZone Number Args RefreshRate`

- Aliases to "thermaln": so `ThermalZone 0 []` can be used in template
  as `%thermal0%`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `temp`
- Default template: `<temp>C`
- This plugin works only on sytems with devices having thermal zone.
  Check directories in `/sys/class/thermal` for possible values of the
  zone number (e.g., 0 corresponds to `thermal_zone0` in that
  directory).
- Example:

         Run ThermalZone 0 ["-t","<id>: <temp>C"] 30

#### `Thermal Zone Args RefreshRate`

- **This plugin is deprecated. Use `ThermalZone` instead.**

- Aliases to the Zone: so `Thermal "THRM" []` can be used in template
  as `%THRM%`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `temp`
- Default template: `Thm: <temp>C`
- This plugin works only on sytems with devices having thermal zone.
  Check directories in /proc/acpi/thermal_zone for possible values.
- Example:

         Run Thermal "THRM" ["-t","iwl4965-temp: <temp>C"] 50

### `CpuFreq Args RefreshRate`

- Aliases to `cpufreq`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `cpu0`, `cpu1`, ..,  `cpuN`
- Default template: `Freq: <cpu0>GHz`
- This monitor requires acpi_cpufreq module to be loaded in kernel
- Example:

         Run CpuFreq ["-t", "Freq:<cpu0>|<cpu1>GHz", "-L", "0", "-H", "2",
                      "-l", "lightblue", "-n","white", "-h", "red"] 50

### `CoreTemp Args RefreshRate`

- Aliases to `coretemp`
- Args: default monitor arguments (see below)
- Variables that can be used with the `-t`/`--template` argument:
	    `core0`, `core1`, ..,  `coreN`
- Default template: `Temp: <core0>C`
- This monitor requires coretemp module to be loaded in kernel
- Example:

         Run CoreTemp ["-t", "Temp:<core0>|<core1>C",
                       "-L", "40", "-H", "60",
                       "-l", "lightblue", "-n", "gray90", "-h", "red"] 50

### `Volume Mixer Element Args RefreshRate`

- Aliases to the mixer name and element name separated by a colon. Thus,
  `Volume "default" "Master" [] 10` can be used as `%default:Master%`.
- Args: default monitor arguments (see below). Also accepts:
    - `-O` _string_ On string
        - The string used in place of `<status>` when the mixer element
          is on. Defaults to "[on]".
        - Long option: `--on`
    - `-o` _string_ Off string
        - The string used in place of `<status>` when the mixer element
          is off. Defaults to "[off]".
        - Long option: `--off`
    - `-C` _color_ On color
        - The color to be used for `<status>` when the mixer element
          is on. Defaults to "green".
        - Long option: `--onc`
    - `-c` _color_ Off color
        - The color to be used for `<status>` when the mixer element
          is off. Defaults to "red".
        - Long option: `--offc`
    - `--highd` _number_ High threshold for dB. Defaults to -5.0.
    - `--lowd` _number_ Low threshold for dB. Defaults to -30.0.
- Variables that can be used with the `-t`/`--template` argument:
            `volume`, `volumebar`, `dB`, `status`
- Note that `dB` might only return 0 on your system. This is known
  to happen on systems with a pulseaudio backend.
- Default template: `Vol: <volume>% <status>`
- Requires the package [alsa-core] and [alsa-mixer] installed in your
  system. In addition, to activate this plugin you must pass
  `--flags="with_alsa"` during compilation.

### `MPD Args RefreshRate`

- This monitor will only be compiled if you ask for it using the
  `with_mpd` flag. It needs [libmpd] 5.0 or later (available on Hackage).
- Aliases to `mpd`
- Args: default monitor arguments (see below). In addition you can provide
  `-P`, `-S` and `-Z`, with an string argument, to represent the
  playing, stopped and paused states in the `statei` template field.
  The environment variables `MPD_HOST` and `MPD_PORT` are used to configure the
  mpd server to communicate with.
- Variables that can be used with the `-t`/`--template` argument:
             `bar`, `state`, `statei`, `volume`, `length`
             `lapsed`, `remaining`,
             `plength` (playlist length), `ppos` (playlist position)
             `name`, `artist`, `composer`, `performer`
             `album`, `title`, `track`, `file`, `genre`
- Default template: `MPD: <state>`
- Example (note that you need "--" to separate regular monitor options from
  MPD's specific ones):

         Run MPD ["-t",
                  "<composer> <title> (<album>) <track>/<plength> <statei> ",
                  "--", "-P", ">>", "-Z", "|", "-S", "><"] 10

### `Mpris1 PlayerName Args RefreshRate`

- Aliases to `mpris1`
- Requires [dbus-core] and [text] packages.
  To activate, pass `--flags="with_mpris"` during compilation.
- PlayerName: player supporting MPRIS v1 protocol, in lowercase.
- Args: default monitor arguments.
- Variables that can be used with the `-t`/`--template` argument:
            `album`, `artist`, `arturl`, `length`, `title`, `tracknumber`
- Default template: `<artist> - <title>`
- Example:

         Run Mpris1 "clementine" ["-t",
                                  "<artist> - [<tracknumber>] <title>"] 10

### `Mpris2 PlayerName Args RefreshRate`

- Just like Mpris1.
  Supposed to be used with mediaplayers which support MPRIS v2.

### `Mail Args Alias`

- Args: list of maildirs in form
  `[("name1","path1"),...]`. Paths may start with a '~'
  to expand to the user's home directory.
- This plugin requires inotify support in your linux kernel and the
  [hinotify] package. To activate, pass `--flags="with_inotify"`
  during compilation.
- Example:

         Run Mail [("inbox", "~/var/mail/inbox"),
                   ("lists", "~/var/mail/lists")]
                  "mail"

### `MBox Mboxes Opts Alias`

- Mboxes a list of mbox files of the form `[("name", "path", "color")]`,
  where name is the displayed name, path the absolute or relative (to
  BaseDir) path of the mbox file, and color the color to use to display
  the mail count (use an empty string for the default).
- Opts is a possibly empty list of options, as flags. Possible values:
   -a  --all (no arg)  Show all mailboxes, even if empty.
   -d dir  --dir dir a string giving the base directory where mbox files with
                     a relative path live.
   -p prefix --prefix prefix  a string giving a prefix for the list
                      of displayed mail coints
   -s suffix --suffix suffix  a string giving a suffix for the list
                      of displayed mail coints
- Paths may start with a '~' to expand to the user's home directory.
- This plugin requires inotify support in your linux kernel and the
  [hinotify] package. To activate, pass `--flags="with_inotify"`
  during compilation.
- Example. The following command look for mails in `/var/mail/inbox`
  and `~/foo/mbox`, and will put a space in front of the printed string
  (when it's not empty); it can be used in the template with the alias
  `mbox`:

         Run MBox [("I ", "inbox", "red"), ("O ", "~/foo/mbox", "")]
                  ["-d", "/var/mail/", "-p", " "] "mbox"

### `XPropertyLog PropName`

- Aliases to `PropName`
- Reads the X property named by `PropName` (a string) and displays its
  value. The [samples/xmonadpropwrite.hs script] in xmobar's
  distribution can be used to set the given property from the output
  of any other program or script.

[samples/xmonadpropwrite.hs script]: https://github.com/jaor/xmobar/raw/master/samples/xmonadpropwrite.hs

### `NamedXPropertyLog PropName Alias`

- Same as XPropertyLog, but a custom alias can be specified.

### `Brightness Args RefreshRate`

- Aliases to `bright`
- Args: default monitor arguments (see below), plus the following specif ones:
    - `-D`: directory in `/sys/class/backlight/` with files in it
       (default: "acpi_video0")
    - `-C`: file with the current brightness (default:
       actual_brightness)
    - `-M`: file with the maximum brightness (default:
       max_brigtness)
- Variables that can be used with the `-t`/`--template` argument:
	    `hbar`, `percent`, `bar`
- Default template: `<percent>`
- Example:

       Run Brightness ["-t", "<bar>"] 60

### `Kbd Opts`

- Registers to XKB/X11-Events and output the currently active keyboard layout.
  Supports replacement of layoutnames.
- Aliases to `kbd`
- Opts is a list of tuple:
    -  first element of the tuple is the search string
    -  second element of the tuple is the corresponding replacement
- Example:

		Run Kbd [("us(dvorak)", "DV"), ("us", "US")]


## Monitor Plugins Commands Arguments

These are the arguments that can be used for internal commands in the
`commands` configuration option:

- `-t` _string_  Output template
    - Template for the monitor output. Field names must be enclosed
      between pointy brackets (`<foo>`) and will be substituted by the
      computed values. You can also specify the foreground (and
      optionally, background) color for a region by bracketing it
      between `<fc=fgcolor>` (or `<fc=fgcolor,bgcolor>`) and
      `</fc>`. The rest of the template is output verbatim.
    - Long option: `--template`
    - Default value: per monitor (see above).
- `-H` _number_ The high threshold.
    - Numerical values higher than _number_ will be displayed with the
      color specified by `-h` (see below).
    - Long option: `--High`
    - Default value: 66
- `-L` _number_ The low threshold.
    - Numerical values higher than _number_ and lower than the high
      threshold will be displayed with the color specified by `-m`
      (see below). Values lower than _number_ will use the `-l` color.
    - Long option: `--Low` - Default value: 80
    - Default value: 33
- `-h` _color_  High threshold color.
    - Color for displaying values above the high threshold. _color_ can
      be either a name (e.g. "blue") or an hexadecimal RGB (e.g.
      "#FF0000").
    - Long option: `--high`
    - Default: none (use the default foreground).
- `-n` _color_  Color for 'normal' values
    - Color used for values greater than the low threshold but lower
      than the high one.
    - Long option: `--normal`
    - Default: none (use the default foreground).
- `-l` _color_  The low threshold color
    - Color for displaying values below the low threshold.
    - Long option: `--low`
    - Default: none (use the default foreground).
- `-S` _boolean_ Display optional suffixes
    - When set to a true designator ("True", "Yes" or "On"), optional
      value suffixes such as the '%' symbol or optional units will be
      displayed.
    - Long option: `--suffix`
    - Default: False.
- `-p` _number_ Percentages padding
    - Width, in number of digits, for quantities representing
      percentages. For instance `-p 3` means that all percentages
      in the monitor will be represented using 3 digits.
    - Long option: `--ppad`
    - Default value: 0 (don't pad)
- `-d` _number_ Decimal digits
    - Number of digits after the decimal period to use in float values.
    - Long option: `--ddigits`
    - Default value: 0 (display only integer part)
- `-m` _number_ Minimum field width
    - Minimum width, in number of characters, of the fields in the
      monitor template. Values whose printed representation is shorter
      than this value will be padded using the padding characters
      given by the `-c` option with the alignment specified by `-a`
      (see below).
    - Long option: `--minwidth`
    - Default: 0
- `-M` _number_ Maximum field width
    - Maximum width, in number of characters, of the fields in the
      monitor template. Values whose printed representation is longer
      than this value will be truncated.
    - Long option: `--maxwidth`
    - Default: 0 (no maximum width)
- `-w` _number_ Fixed field width
    - All fields will be set to this width, padding or truncating as
      needed.
    - Long option: `--width`
    - Default: 0 (variable width)
- `-c` _string_
    - Characters used for padding. The characters of _string_ are used
      cyclically. E.g., with `-P +- -w 6`, a field with value "foo"
      will be represented as "+-+foo".
    - Long option: `--padchars`
    - Default value: " "
- `-a` r|l Field alignment
    - Whether to use right (r) or left (l) alignment of field values
      when padding.
    - Long option: `--align`
    - Default value: r (padding to the left)
- `-b` _string_ Bar background
    - Characters used, cyclically, to draw the background of bars.
      For instance, if you set this option to "·.", an empty bar will
      look like this: `·.·.·.·.·.`
    - Long option: `--bback`
    - Default value: ":"
- `-f` _string_ Bar foreground
    - Characters used, cyclically, to draw the foreground of bars.
    - Long option: `--bfore`
    - Default value: "#"
- `-W` _number_ Bar width
    - Total number of characters used to draw bars.
    - Long option: `--bwidth`
    - Default value: 10

Commands' arguments must be set as a list. E.g.:

    Run Weather "EGPF" ["-t", "<station>: <tempC>C"] 36000

In this case xmobar will run the weather monitor, getting information
for the weather station ID EGPF (Glasgow Airport, as a homage to GHC)
every hour (36000 tenth of seconds), with a template that will output
something like:

    Glasgow Airport: 16.0C

## Executing External Commands

In order to execute an external command you can either write the
command name in the template, in this case it will be executed without
arguments, or you can configure it in the "commands" configuration
option list with the Com template command:

`Com ProgramName Args Alias RefreshRate`

- ProgramName: the name of the program
- Args: the arguments to be passed to the program at execution time
- RefreshRate: number of tenths of second between re-runs of the
  command. A zero or negative rate means that the command will be
  executed only once.
- Alias: a name to be used in the template. If the alias is en empty
  string the program name can be used in the template.

E.g.:

        Run Com "uname" ["-s","-r"] "" 0

can be used in the output template as `%uname%` (and xmobar will call
_uname_ only once), while

        Run Com "date" ["+\"%a %b %_d %H:%M\""] "mydate" 600

can be used in the output template as `%mydate%`

## Other Plugins

`StdinReader`

- Aliases to StdinReader
- Displays any text received by xmobar on its standard input.

`Date Format Alias RefreshRate`

- Format is a time format string, as accepted by the standard ISO C
  `strftime` function (or Haskell's `formatCalendarTime`).
- Sample usage: `Run Date "%a %b %_d %Y <fc=#ee9a00>%H:%M:%S</fc>" "date" 10`

`DateZone Format Locale Zone Alias RefreshRate`

- Format is a time format string, as accepted by the standard ISO C
  `strftime` function (or Haskell's `formatCalendarTime`).
- If Locale is "" the default locale of the system is used, otherwise the given
  locale. If there are more instances of DateZone, using "" as input for Locale
  is not recommended.
- Zone is the name of the TimeZone. It is assumed that the tz database is stored
  in /usr/share/zoneinfo/. If "" is given as Zone, the default system time is
  used.
- Sample usage:
  `Run DateZone "%a %H:%M:%S" "de_DE.UTF-8" "Europe/Vienna" "viennaTime" 10`

`CommandReader "/path/to/program" Alias`

- Runs the given program, and displays its standard output.

`PipeReader "/path/to/pipe" Alias`

- Reads its displayed output from the given pipe.

`XMonadLog`

- Aliases to XMonadLog
- Displays information from xmonad's `_XMONAD_LOG`. You can set this
  property by using `xmonadPropLog` as your log hook in xmonad's
  configuration, as in the following example (more info [here]):

        main = do
          spawn "xmobar"
          xmonad $ defaultConfig {
            logHook = dynamicLogString defaultPP >>= xmonadPropLog
          }
   This plugin can be used as a sometimes more convenient alternative
   to `StdinReader`. For instance, it allows you to (re)start xmobar
   outside xmonad.

[here]: http://xmonad.org/xmonad-docs/xmonad-contrib/XMonad-Hooks-DynamicLog.html

Plugins
=======

## Writing a Plugin

Writing a plugin for xmobar should be very simple. You need to create
a data type with at least one constructor.

Next you must declare this data type an instance of the `Exec` class, by
defining the 1 needed method (alternatively `start` or `run`) and 2
optional ones (alias and rate):

        start :: e -> (String -> IO ()) -> IO ()
        run   :: e -> IO String
        rate  :: e -> Int
        alias :: e -> String

`start` must receive a callback to be used to display the `String`
produced by the plugin. This method can be used for plugins that need
to perform asynchronous actions. See `Plugins/PipeReader.hs` for an
example.

`run` can be used for simpler plugins. If you define only `run` the
plugin will be run every second. To overwrite this default you just
need to implement `rate`, which must return the number of tenth of
seconds between every successive runs. See `Plugins/HelloWorld.hs` for
an example of a plugin that runs just once, and `Plugins/Date.hs` for
one that implements `rate`.

Notice that Date could be implemented as:

        instance Exec Date where
            alias (Date _ a _) = a
            start (Date f _ r) = date f r

        date :: String -> Int -> (String -> IO ()) -> IO ()
        date format r callback = do go
            where go = do
                    t <- toCalendarTime =<< getClockTime
                    callback $ formatCalendarTime defaultTimeLocale format t
                    tenthSeconds r >> go

This implementation is equivalent to the one you can read in
`Plugins/Date.hs`.

`alias` is the name to be used in the output template. Default alias
will be the data type constructor.

Implementing a plugin requires importing the plugin API (the `Exec`
class definition), that is exported by `Plugins.hs`. So you just need
to import it in your module with:

        import Plugins

After that your type constructor can be used as an argument for the
Runnable type constructor `Run` in the `commands` list of the
configuration options.

This requires importing your plugin into `Config.hs` and adding your
type to the type list in the type signature of `Config.runnableTypes`.

For a very basic example see `samples/Plugins/HelloWorld.hs` or the
other plugins that are distributed with xmobar.

## Installing/Removing a Plugin

Installing a plugin should require 3 steps. Here we are going to
install the HelloWorld plugin that comes with xmobar, assuming that
you copied it to `src/Plugins`:

1. import the plugin module in `Config.hs`, by adding:

        import Plugins.HelloWorld

2. add the plugin data type to the list of data types in the type
   signature of `runnableTypes` in `Config.hs`. For instance, for the
   HelloWorld plugin, change `runnableTypes` into:

        runnableTypes :: Command :*: Monitors :*: HelloWorld :*: ()
        runnableTypes = undefined

3. Rebuild and reinstall xmobar. Now test it with:

        xmobar Plugins/helloworld.config

As you may see in the example configuration file, the plugin can be
used by adding, in the `commands` list:

        Run HelloWorld

and, in the output template, the alias of the plugin:

        %helloWorld%

That's it.

To remove a plugin, just remove its type from the type signature of
runnableTypes and remove the imported modules.

To remove the system monitor plugin:

1. remove, from `Config.hs`, the line

        import Plugins.Monitors

2. in `Config.hs` change

         runnableTypes :: Command :*: Monitors :*: ()
         runnableTypes = undefined

    to

         runnableTypes :: Command :*: ()
         runnableTypes = undefined

3. rebuild xmobar.

Authors and credits
===================

Andrea Rossato originally designed and implemented xmobar up to
version 0.11.1. Since then, it is maintained and developed by [Jose
Antonio Ortega Ruiz](http://hacks-galore.org/jao/), with the help of
the greater Haskell community.

In particular, xmobar [incorporates patches] by Ben Boeckel, Roman
Cheplyaka, John Goerzen, Juraj Hercek, Tomas Janousek, Spencer
Janssen, Lennart Kolmodin, Krzysztof Kosciuszkiewicz, Dmitry
Kurochkin, Svein Ove, Martin Perner, Jens Petersen, Petr Rockai,
Andrew Sackville-West, Alexander Solovyov, Artem Tarasov, Sergei
Trofimovich, Thomas Tuegel, Jan Vornberger, Daniel Wagner and Norbert
Zeh.

[incorporates patches]: http://www.ohloh.net/p/xmobar/contributors

## Thanks

__Andrea Rossato__:

Thanks to Robert Manea and Spencer Janssen for their help in
understanding how X works. They gave me suggestions on how to solve
many problems with xmobar.

Thanks to Claus Reinke for make me understand existential types (or at
least for letting me think I grasp existential types...;-).

__jao__:

Thanks to Andrea for creating xmobar in the first place, and for
giving me the chance to contribute.

Useful links
============

- [Github page].
- [Mailing list].
- [xmobar's Ohloh page].

- To understand the internal mysteries of xmobar you may try reading
  [this tutorial] on X Window Programming in Haskell.

- My [sawflibs] project includes a module to automate running xmobar
  in [sawfish].

[xmobar's Ohloh page]: https://www.ohloh.net/p/xmobar
[this tutorial]: http://www.haskell.org/haskellwiki/X_window_programming_in_Haskell
[sawflibs]: http://github.com/jaor/sawflibs

License
=======

This software is released under a BSD-style license. See [LICENSE] for
more details.

Copyright &copy; 2007-2010 Andrea Rossato

Copyright &copy; 2010-2012 Jose Antonio Ortega Ruiz

[Github]: http://github.com/jaor/xmobar/
[Github page]: http://github.com/jaor/xmobar
[Hackage]: http://hackage.haskell.org/package/xmobar/
[LICENSE]: https://github.com/jaor/xmobar/raw/master/LICENSE
[Mailing list]: http://projects.haskell.org/cgi-bin/mailman/listinfo/xmobar
[MPD]: http://mpd.wikia.com/
[X11-xft]: http://hackage.haskell.org/package/X11-xft/
[i3status]: http://i3wm.org/i3status/
[i3status manual]: http://i3wm.org/i3status/manpage.html#_using_i3status_with_xmobar
[iwlib]: http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux/Tools.html
[hinotify]: http://hackage.haskell.org/package/hinotify/
[libmpd]: http://hackage.haskell.org/package/libmpd/
[dbus-core]: http://hackage.haskell.org/package/dbus-core
[text]: http://hackage.haskell.org/package/text
[sawfish]: http://sawfish.wikia.com/
[utf8-string]: http://hackage.haskell.org/package/utf8-string/
[alsa-core]: http://hackage.haskell.org/package/alsa-core
[alsa-mixer]: http://hackage.haskell.org/package/alsa-mixer
[timezone-olson]: http://hackage.haskell.org/package/timezone-olson
[timezone-series]: http://hackage.haskell.org/package/timezone-series
