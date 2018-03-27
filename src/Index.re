let defaultTZ = "Pacific/Auckland";

Tzdb.getTime(defaultTZ, time =>
  ReactDOMRe.renderToElementWithId(<Clock time tz=defaultTZ />, "clock")
);