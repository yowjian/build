#!/usr/bin/python3
import pith
if __name__ == '__main__':
  args = pith.get_args()
  if args.mode == 'gui': pith.setup_gui(args)

