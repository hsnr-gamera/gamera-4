import sys
import textwrap


def gamera_gui():
	print("Loading GAMERA...")
	print("Use 'gamera_gui --help' to display command line options")
	try:
		from gamera.config import config
		from gamera.gui import gui

		config.parse_args(sys.argv[1:])
		gui.run()
	except Exception as e:
		if not isinstance(e, (SystemExit, KeyboardInterrupt)):
			print("Gamera made the following fatal error:")
			print()
			print(textwrap.fill(str(e)))
			print()
			print("=" * 75)
			print("The traceback is below.  Please send this to the Gamera developers")
			print("if you feel you got here in error.")
			print("-" * 75)