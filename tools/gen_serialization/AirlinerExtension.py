from jinja2.ext import Extension


class AirlinerExtension(Extension):

    def __init__(self, environment):
        super(AirlinerExtension, self).__init__(environment)

		environment.extend(
			trim_blocks=False,
			lstrip_blocks=False,
			keep_trailing_newline=False
		)
