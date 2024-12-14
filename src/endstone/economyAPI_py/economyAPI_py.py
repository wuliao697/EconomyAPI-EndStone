from endstone.plugin import Plugin

class economyAPI_py(Plugin):
    def on_load(self) -> None:
        self.logger.info("economyAPI hook Loading!")

    def on_enable(self) -> None:
        self.logger.info("economyAPI hook Activated!")

    def on_disable(self) -> None:
        self.logger.info("economyAPI hook called!")