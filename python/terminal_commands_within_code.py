import os, subprocess

### Doesn't work (yet)
#runstr = './mcfm'
#subprocess.run(runstr,shell=True)

# Works but horribly slow, can't be terminated by CRTL+C
#subprocess.Popen(["./mcfm"])

# Works but horribly slow
subprocess.call(["./mcfm"])
