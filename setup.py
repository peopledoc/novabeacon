from setuptools import setup

if __name__ == '__main__':  # ``import setup`` doesn't trigger setup().
    setup(name='novabeacon',
          version='0.1',
          description="""Python lib to save event for beacon.""",
          keywords='',
          author='Novapost',
          author_email='boris.feld@novapost.fr',
          url='https://github.com/novagile/novabeacon',
          license='Public Domain',
          packages=['beacon'],
          zip_safe=False
    )
