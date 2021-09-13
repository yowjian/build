import build as build_

def test(out: build_.BuildOutput) -> bool:
    stdout, stderr, retcode = out['minizinc']
    return (b"UNSATISFIABLE" in stdout or b"UNSATISFIABLE" in stderr) and retcode == 0