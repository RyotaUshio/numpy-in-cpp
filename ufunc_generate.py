import re, sys

signature     = re.compile(r'^(\w+)\((.+)\)$', re.MULTILINE)
cppexpression = re.compile(r'^cpp\[(.+)\]')
equivalent    = re.compile(r'^eq\[(.+)\]')
description   = re.compile(r'^\w.*\.$', re.MULTILINE)
section       = re.compile(r'^\w+$')
comment       = re.compile(r'^#.*')

def main(source, target):
    with open(source) as f, open(target, 'w') as g:
        g.write("// https://numpy.org/doc/stable/reference/ufuncs.html\n\n")
        g.write("#pragma once\n#include <cmath>\n#include <numeric>\nnamespace numpy {\n\n")

        decls = []
        
        for line in f:
            sig = signature.match(line)
            cpp = cppexpression.match(line)
            eq  = equivalent.match(line)
            des = description.match(line)
            sec = section.match(line)
            com = comment.match(line)

            if com:
                continue

            elif sig:
                name, args = sig.groups()
                binary = 'x1, x2' in args
                unary = not binary and 'x' in args

                if unary:
                    decls += [f'  ufunc_unary<_{name}> {name};']
                elif binary:
                    decls += [f'  ufunc_binary<_{name}> {name};']
                else:
                    raise Exception(f'{name} is neither unary or binary?')

            elif cpp:
                cppexp = cpp.groups()[0]
                if unary:
                    g.write("\n".join([
                         "  template <class Type>",
                        f"  struct _{name} {{",
                        f"    constexpr _{name}() = default;",
                        f"    auto operator()(const Type& x) -> decltype({cppexp}) {{",
                        f"      return {cppexp};",
                         "    }",
                         "  };\n\n"
                    ]))
                elif binary:
                    g.write("\n".join([
                         "  template <class Type1, class Type2>",
                        f"  struct _{name} {{",
                        f"    constexpr _{name}() = default;",
                        f"    constexpr auto operator()(const Type1& x1, const Type2& x2) -> decltype({cppexp}) {{",
                        f"      return {cppexp};",
                         "    }",
                         "  };\n\n"
                    ]))

            elif eq:
                decls[-1] = f"  auto {name} = {eq.groups()[0]};"
                    
            elif des:
                decls += ['\t// ' + des.group() + '\n']

            elif sec:
                decls += [f'\n\n  /{f" {sec.group()} ":*^80}/\n']

        decls += ["\n}\n"]
        g.write("".join(decls))

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f"usage: python {sys.argv[0]} [source] [target]")
        sys.exit(1)
    main(sys.argv[1], sys.argv[2])
    
