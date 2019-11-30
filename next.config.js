const path = require("path");
const withTM = require("next-transpile-modules");
const withCSS = require("@zeit/next-css");

module.exports = withCSS(
  withTM({
    pageExtensions: ["jsx", "js", "bs.js"],
    transpileModules: ["bs-platform"],
    webpack(config) {
      return config;
    }
  })
);
