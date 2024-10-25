'''
This module is starting point of the app
'''

from main.controller import MainMenuController

def start()->None:
    '''
    This function will start the tool
    '''
    main_controller = MainMenuController()
    main_controller.start()

start()