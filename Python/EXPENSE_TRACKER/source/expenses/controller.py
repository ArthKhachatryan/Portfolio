"""This module will contain all expense tracking controllers.
"""
from .view import ManageExpensesView
from .model import ExpensesModel

class ManageExpensesController:
    """This controller will handle manage expenses activities.
    (i.e. add new expenses or view the history)
    """
    def view_history(self)->None:
        """This function will show expense history
        """
        expenses_view = ManageExpensesView()

        expenses_model = ExpensesModel()
        all_expenses = expenses_model.list()

        expenses_view.display_expense_history(all_expenses)


    def add_new_expense(self)->None:
        """This function will add new expense to the DB
        """
        expense_view = ManageExpensesView()
        expense_info = expense_view.get_expense_info()

        expenses_model = ExpensesModel()
        expenses_model.create(
            category = expense_info["category"],
            amount = expense_info["amount"],
            date = expense_info["date"]
        )


    def start(self)->None:
        """Start the controller
        """

        manage_exp_view = ManageExpensesView()
        selected_menu = manage_exp_view.menu_options()

        if selected_menu == 1:
            self.add_new_expense()
        elif selected_menu == 2:
            self.view_history()
        else:
            print("Invalid menu selected. Try again.")
            return self.start()

        return self.start()

    def starter (self)->None:
        """Starter the controller
        """

        expenses_model = ExpensesModel()
        reports = expenses_model.load_reports()
        
        reports_view = ManageExpensesView()
        reports_view.see_reports(reports)